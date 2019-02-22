#ifndef PRIMITIVES
	#define PRIMITIVES

#include "globals.glsl"
#include "quaternions.glsl"
#include "cut.glsl"

mat2 r2(float th)
{
	vec2 a = sin(vec2(PI * 0.5, 0) + th);
	return mat2(a, -a.y, a.x);
}

float map(vec3 p)
{
	float a = atan(p.z, p.x);
	p.xz *= r2(a);
	p.x -= 2.5;
	p.xy *= r2(a * 0.5);
	vec2 d = abs(p.xy) - vec2(0.5, 0.001);
	return min(max(d.x, d.y), 0) + length(max(d, 0));
}

vec3 calcNormal(vec3 pos)
{
	vec2 e = vec2(1.0, -1.0) * 0.5773 * 0.0005;
	return normalize(
		e.xyy * map(pos + e.xyy) +
		e.yyx * map(pos + e.yyx) +
		e.yxy * map(pos + e.yxy) +
		e.xxx * map(pos + e.xxx));
}

bool iSpecial(vec3 ro, vec3 rd, out float tt, out vec3 n)
{
	float t = 0;
	float d = 0;
	vec3 p = ZERO;
	int i = 0;
	do
	{
		p = ro + rd * t;
		d = map(p);
		t += d * .9;
		i++;
	} while (i < 150 && t < 100.0 && d > 0.0001);
	tt = t;
	n = calcNormal(ro + rd * tt);
	return (t < 100.0);
}

vec2 iQuadric(vec3 ro, vec3 rd, mat4 matrix)
{
	vec4 o = vec4(ro, 1);
	vec4 d = vec4(rd, 0);

	float a = dot(d, matrix * d);
	float b = 2 * dot(d, matrix * o);
	float c = dot(o, matrix * o);

	if(abs(a) < 0.000001)
	{
		vec2 result = vec2(-c/b, -1000000*sign(b));
		if(result.x < 0 && result.y > 0)
			return result.yx;
		return result.xy;
	}

	vec2 result;
	if(!analyticalQuadratic(a, b, c, result))
		return vec2(INFINITY);

	if (result.x < 0.0 && result.y < 0.0)
		return (result.x < result.y) ? result.yx : result.xy;
	if (result.x > 0.0 && result.y > 0.0)
		return (result.x < result.y) ? result.xy : result.yx;
	return (result.x > result.y) ? result.xy : result.yx;
}

vec3 nQuadric(vec3 hitPos, mat4 matrix)
{
	vec3 result;
	result.x = matrix[0][0]*hitPos.x + matrix[1][0]*hitPos.y + matrix[2][0]*hitPos.z + matrix[3][0];
	result.y = matrix[1][0]*hitPos.x + matrix[1][1]*hitPos.y + matrix[2][1]*hitPos.z + matrix[3][1];
	result.z = matrix[2][0]*hitPos.x + matrix[2][1]*hitPos.y + matrix[2][2]*hitPos.z + matrix[3][2];

	return normalize(result);
}

  ////////////////////////////////////////////////////
 ////   Sphere  -->  [ x² + y² + z² - r² = 0 ]   ////
////////////////////////////////////////////////////

vec2 iSphere(vec3 ro, vec3 rd, vec4 sph)
{
	ro -= sph.xyz;
	float b = dot(ro, rd);
	float c = dot(ro, ro) - sph.w * sph.w;
	float h = b * b - c;
	if (h < 0.0) { return vec2(INFINITY); }
	float t = sqrt(h);
	vec2 res = -b + vec2(-t, t);

	if (res.x < 0.0 && res.y < 0.0)
		return (res.x < res.y) ? res.yx : res.xy;
	if (res.x > 0.0 && res.y > 0.0)
		return (res.x < res.y) ? res.xy : res.yx;
	return (res.x > res.y) ? res.xy : res.yx;
}

vec3 nSphere(vec3 wpos, vec3 pos)
{
	wpos -= pos;
	return normalize(wpos);
}

vec2 cSphere(vec3 p, vec4 sph)
{
	p -= sph.xyz;
	float o = atan(p.z, p.x) / PI;
	// float o = abs(atan(p.z, p.x)) / PI;
	float O = acos(p.y / sph.w) / PI;
	return vec2(o, O);
}


  /////////////////////////////////////////////////
 ////   Cylinder  -->  [ x² + y² - r² = 0 ]   ////
/////////////////////////////////////////////////

vec2 iCylinder(vec3 ro, vec3 rd, vec4 cy)
{
	// ro -= cy.xyz;
	float a = dot(rd.xz, rd.xz);
	float b = dot(ro.xz, rd.xz);
	float c = dot(ro.xz, ro.xz) - cy.w * cy.w;
	float h = b * b - a * c;
	if (h < 0) { return vec2(INFINITY); }
	float t = sqrt(h);
	vec2 res = (-b + vec2(-t, t)) / a;

	if (res.x < 0.0 && res.y < 0.0)
		return (res.x < res.y) ? res.yx : res.xy;
	if (res.x > 0.0 && res.y > 0.0)
		return (res.x < res.y) ? res.xy : res.yx;
	return (res.x > res.y) ? res.xy : res.yx;
}

vec3 nCylinder(vec3 hit, vec3 pos, vec3 dir)
{
	return normalize(hit - dir*dot(hit-pos, dir) - pos);
}

vec2 cCylinder(vec3 p, vec4 cy)
{
	// p -= cy.xyz;
	float o = abs(atan(p.z, p.x)) / PI;
	// float o = acos(p.x / cy.w) / PI;
	float O = p.y;
	return vec2(o, O);
}


  ////////////////////////////
 ////   CappedCylinder   ////
////////////////////////////

vec2 iPlaneProper(vec3 ro, vec3 rd, vec4 p)
{
	float x = -(dot(ro, p.xyz) + p.w) / dot(rd, p.xyz);
	float y = -9999999999.9 * dot(rd, p.xyz);
	if (x < 0.0)
		return vec2(y, x);
	return vec2(x, y);
}

float iPlane(vec3 ro, vec3 rd, vec4 p)
{
	float denom = dot(p.xyz, rd);
	if(abs(denom) < Epsilon)
		return(-1);
	return (-p.w - dot(p.xyz, ro)) / denom;
}

vec2 iCappedCylinder(vec3 ro, vec3 rd, vec4 cy, float z)
{
	ro -= cy.xyz;
	float a = dot(rd.xz, rd.xz);
	float b = dot(ro.xz, rd.xz);
	float c = dot(ro.xz, ro.xz) - cy.w * cy.w;
	float h = b * b - a * c;
	if (h < 0.0) { return vec2(INFINITY); }
	float t = sqrt(h);

	float t1 = (-b - t) / a;
	float t2 = (-b + t) / a;
	float z1 = ro.y + rd.y * t1;
	float z2 = ro.y + rd.y * t2;
	if (abs(z2) > z && abs(z1) > z)
		return vec2(INFINITY);
	if (abs(z1) >= z)
		t1 = iPlane(ro, rd, vec4(0.0, sign(z1), 0.0, -z));
	if (abs(z2) >= z)
		t2 = iPlane(ro, rd, vec4(0.0, sign(z2), 0.0, -z));
	return vec2(t1, t2);
}

vec3 nCappedCylinder(vec3 wpos, vec4 cy, float z)
{
	vec3 p = wpos - cy.xyz;
	if (abs(p.y) >= z - Epsilon)
		return vec3(0.0, sign(p.y), 0.0);
	return normalize(p * vec3(1.0, 0.0, 1.0));
}

vec2 cCappedCylinder(vec3 p, vec4 cy, float z)
{
	p -= cy.xyz;
	float o = abs(atan(p.z, p.x)) / PI;
	// float o = acos(p.x / cy.w) / PI;
	float O = p.y / (z * 2.) + .5;
	if (abs(p.y) >= z - Epsilon)
	{
		o = length(p.xz) / cy.w;
		O = (p.y > 0.0) ? 1.0 : 0.0;
	}
	return vec2(o, O);
}


  /////////////////////
 ////   Capsule   ////
/////////////////////

vec2 iCapsule(vec3 ro, vec3 rd, vec4 cy, float z)
{
	vec2 form = iCylinder(ro, rd, cy);

	vec2 cutter = iPlaneProper(ro, rd, vec4(-UP, z));
	vec2 h = cutJustRoots(form, cutter);
	cutter = iPlaneProper(ro, rd, vec4(UP, z));
	h = cutJustRoots(h, cutter);

	vec2 adder = iSphere(ro, rd, vec4(0.0, z, 0.0, cy.w));
	h = addJustRoots(h, adder);
	adder = iSphere(ro, rd, vec4(0.0, -z, 0.0, cy.w));
	h = addJustRoots(h, adder);

	return h;
}

vec3 nCapsule(vec3 wpos, vec4 cy, float z)
{
	vec3 p = wpos - cy.xyz;
	if (abs(p.y) >= z - Epsilon)
		return nSphere(p, vec3(0.0, z * sign(p.y), 0.0));
	return normalize(p * vec3(1.0, 0.0, 1.0));
}

vec2 iCube(vec3 ro, vec3 rd, vec3 pos, vec3 size)
{
	vec3 m = 1.0 / rd;
    vec3 n = m * ro;
    vec3 k = abs(m) * size;

    vec3 t1 = -n - k;
    vec3 t2 = -n + k;

	vec2 res = vec2(max(max(t1.x, t1.y), t1.z),
					min(min(t2.x, t2.y), t2.z));

    if (res.x > res.y) { return vec2(INFINITY); }

	if (res.x < 0.0 && res.y < 0.0)
		return (res.x < res.y) ? res.yx : res.xy;
	if (res.x > 0.0 && res.y > 0.0)
		return (res.x < res.y) ? res.xy : res.yx;
	return (res.x > res.y) ? res.xy : res.yx;

    // // nor = -sign(rd)*step(t1.yzx,t1.xyz)*step(t1.zxy,t1.xyz);
	// // if (tN < 0)
	// // 	nor = sign(rd)*step(-t2.yzx,-t2.xyz)*step(-t2.zxy,-t2.xyz);
}

vec3 nCube(vec3 wpos, vec3 pos, vec3 size)
{
	wpos -= pos;
	wpos /= size;

	float m = max(max(abs(wpos.x), abs(wpos.y)), abs(wpos.z));
	// vec3 n = step(abs(wpos), vec3(m - .00001)) * sign(wpos);
	vec3 n = normalize(saturate(abs(wpos) - vec3(m - Epsilon))) * sign(wpos);
	return n;
}


  /////////////////////////////////////////////////////////////
 ////   Torus  -->  [ (√(x² + y²) - R)² + z² - r² = 0 ]   ////
/////////////////////////////////////////////////////////////

vec2 iTorus(vec3 ro, vec3 rd, vec3 pos, float R, float r)
{
	ro -= pos;
	float dd = dot(rd,rd); //1.0
	float od = dot(ro,rd);
	float oo = dot(ro,ro) - R*R - r*r;
	float frs = 4.0 * R*R;

	float a = dd*dd; //1.0
	float b = 4.0 * dd * od;
	float c = 2.0 * dd * oo + 4.0 * od*od + frs * rd.z*rd.z;
	float d = 4.0 * oo * od + 2.0 *	frs * ro.z*rd.z;
	float e = oo*oo - frs * (r*r - ro.z*ro.z);

	float root = iCube(ro, rd, ZERO, vec3(vec2(R + r), r)).x;
	if (isinf(root)) { return vec2(INFINITY); }
	vec4 tmp;
	int n = quartic(b, c, d, e, tmp); // A == 1.0, test non normalized RD
	if (n == 4)
	{
		if (tmp.y > tmp.z) { tmp.yz = tmp.zy; }
		if (tmp.x > tmp.y) { tmp.xy = tmp.yx; }
		if (tmp.z > tmp.w) { tmp.zw = tmp.wz; }
		if (tmp.y > tmp.z) { tmp.yz = tmp.zy; }
	}

	// return tmp.xy;
	if (n == 2)
	{
		if (tmp.x > 0.0 && tmp.y > 0.0)
			return tmp.xy;
		return tmp.yx;
	}

	if (n == 4)
	{
		if (tmp.x > 0.0 && tmp.y > 0.0)
			return tmp.xy;
		if (tmp.x < 0.0 && tmp.y > 0.0)
			return tmp.yx;
		if (tmp.y < 0.0 && tmp.z > 0.0)
			return tmp.zw;
		if (tmp.z < 0.0 && tmp.w > 0.0)
			return tmp.wz;
	}

	return vec2(INFINITY);
}

vec3 nTorus(vec3 wpos, vec3 pos, vec2 tor)

{	wpos -= pos;
	return normalize(wpos * (dot(wpos,wpos) - tor.y*tor.y - tor.x*tor.x * vec3(1.0, 1.0, -1.0)));
}

#endif
