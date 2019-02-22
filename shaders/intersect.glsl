#ifndef INTERSECT
	#define INTERSECT

#include "structures.glsl"
#include "roots.glsl"
#include "primitives.glsl"
#include "globals.glsl"
#include "sampling.glsl"
#include "cut.glsl"

Ray transformRay(Ray pRay, Transform transform)
{
	Ray res;
	res.ro = qMulVec(pRay.ro - transform.pos, transform.rot);
	res.rd = qMulVec(pRay.rd, transform.rot);
	return res;
}

#endif
