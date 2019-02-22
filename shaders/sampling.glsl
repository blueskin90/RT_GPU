#ifndef SAMPLING
	#define SAMPLING

vec3 randomSphereDirection()
{
    vec2 h = vec2(randMe(), randMe()) * vec2(2.0, 6.28318530718) - vec2(1.0, 0.0);
    float phi = h.y;
	return vec3(sqrt(1.0 - h.x*h.x) * vec2(sin(phi), cos(phi)), h.x);
}

vec3 randomHemisphereDirection(vec3 n)
{
	vec3 dr = randomSphereDirection();
	return dot(dr,n) * dr;
}

vec3 ortho(vec3 v)
{
	return abs(v.x) > abs(v.z) ? vec3(-v.y, v.x, 0.0) : vec3(0.0, -v.z, v.y);
}

vec3 getConeSample(vec3 dir, float extent, float seed)
{
	dir = normalize(dir);
	vec3 o1 = normalize(ortho(dir));
	vec3 o2 = normalize(cross(dir, o1));
	vec2 r = vec2(randMe(), randMe());
	r.x = r.x * 2.0 * PI;
	r.y = 1.0 - r.y * extent;
	float oneminus = sqrt(1.0 - r.y*r.y);
	return cos(r.x) * oneminus * o1 + sin(r.x) * oneminus * o2 + r.y * dir;
}

vec3 cosineDirection(in vec3 nor)
{
	float u = randMe();
	float v = randMe();

	float a = 6.2831853 * v;
	u = 2.0 * u - 1.0;
	return normalize(nor + vec3(sqrt(1.0 - u * u) * vec2(cos(a), sin(a)), u));
}

float ff(float n1, float n2, vec3 normal, vec3 incident, float reflectance)
{
	float r0 = (n1-n2) / (n1+n2);
	r0 *= r0;
	float cosX = -dot(normal, incident);
	if (n1 > n2)
	{
		float n = n1/n2;
		float sinT2 = n*n*(1.0-cosX*cosX);
		if (sinT2 > 1.0)
			return 1.0;
		cosX = sqrt(1.0-sinT2);
	}
	float x = 1.0-cosX;
	float ret = r0+(1.0-r0)*x*x*x*x*x;
	ret = (reflectance + (1.0-reflectance) * ret);
	return ret;
}


vec2 randomTrianglePoint(vec2 a, vec2 b, vec2 c, vec2 rand)
{
	rand = (rand.x + rand.y > 1.0) ? 1.0 - rand : rand;

	float aT = 1.0 - rand.x - rand.y;
	float bT = rand.x;
	float cT = rand.y;

	return a*aT + b*bT + c*cT;
}

vec2 get(uint seed)
{
	const vec2 a = vec2( 0.0,    1.0);
    const vec2 b = vec2( 0.866, -0.5);
    const vec2 c = vec2(-0.866, -0.5);

	vec2 randS = vec2(randMe(), randMe());
	return randomTrianglePoint(a, b, c, randS);
}

float ihash(int n)
{
	n = (n << 13) ^ n;
	n = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
	return (1.0 / 2147483647.0) * float(n);
}

float uhash13(uvec3 x)
{
    uint t = x.x + x.y * 2 * (x.y + x.z * 2);
    return ihash(int(t));
}

float noise(vec3 p)
{
    uvec3 i = uvec3(floor(p));
    vec3 t = fract(p);
    vec3 w = t * t * (3.0 - 2.0 * t);

    float c   = uhash13(i + uvec3(0, 0, 0));
    float cx  = uhash13(i + uvec3(1, 0, 0));
    float cy  = uhash13(i + uvec3(0, 1, 0));
    float cxy = uhash13(i + uvec3(1, 1, 0));
    float bot = mix(mix(c, cx, w.x), mix(cy, cxy, w.x), w.y);

    float cz   = uhash13(i + uvec3(0, 0, 1));
    float cxz  = uhash13(i + uvec3(1, 0, 1));
    float cyz  = uhash13(i + uvec3(0, 1, 1));
    float cxyz = uhash13(i + uvec3(1, 1, 1));
    float top = mix(mix(cz, cxz, w.x), mix(cyz, cxyz, w.x), w.y);

    return mix(bot, top, w.z);
}

float fbm(vec3 p)
{
    float s = 0.0;
    float m = 0.0;
    float a = 0.5;
    for (int i = 0; i < 8; i++)
    {
        s += a * noise(p);
        m += a;
        a *= 0.5;
        p *= 2.0;
    }
    return s / m;
}

#endif
