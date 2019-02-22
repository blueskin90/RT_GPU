#ifndef QUATERNIONS
	#define QUATERNIONS

#define QIDENTITY vec4(0.0, 0.0, 0.0, 1.0)

vec4 qMult(vec4 q1, vec4 q2)
{
	vec4 q;
	q.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
	q.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
	q.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);
	q.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
	return q;
}

vec4 createRotation(vec3 axis, float angle)
{
	vec4 q;
	q.xyz = axis * sin(angle * 0.5);
	q.w = cos(angle * 0.5);
	return normalize(q);
}

vec3 qMulVec(vec3 v, vec4 q)
{
	return v + 2.0 * cross(q.xyz, cross(q.xyz, v.xyz) + q.w * v.xyz);
}

vec3 rotateVector(vec3 v, vec3 axis, float angle)
{
  vec4 q = createRotation(axis, angle);
  return qMulVec(v, q);
}

vec4 qInverse(vec4 q)
{
	return (1.0 / dot(q, q)) * q * vec4(vec3(-1.0), 1.0);
}

vec4 qConjugate(vec4 q)
{
	return q * vec4(vec3(-1.0), 1.0);
}

#endif
