#ifndef GLOBALS
	#define GLOBALS

	#define INFINITY 1.0/0.0
	#define PI acos(-1.0)
	#define Epsilon .0005

	#define time ubo.ubotime
	#define frame ubo.uboframe

	#define RIGHT	vec3(1.0, 0.0, 0.0)
	#define UP		vec3(0.0, 1.0, 0.0)
	#define FW		vec3(0.0, 0.0, 1.0)
	#define ZERO 	vec3(0.0, 0.0, 0.0)
	#define ONE		vec3(1.0, 1.0, 1.0)

	#define SPHERE_ID 0
	#define CUBE_ID	1
	#define CAPSULE_ID 2
	#define TORUS_ID 3
	#define PLANE_ID 4
	#define CYLINDER_ID 5
	#define CONE_ID 6

	#define OBJECT_MAX 128

	#define saturate(x) clamp(x, 0.0, 1.0)

	uint pixelID;
	uint iSeed;
	float randMe()
	{
		iSeed = (iSeed ^ 61) ^ (iSeed >> 16);
		iSeed *= 9;
		iSeed = iSeed ^ (iSeed >> 4);
		iSeed *= 0x27d4eb2d;
		iSeed = iSeed ^ (iSeed >> 15);
		return iSeed * (1.0 / float(0xffffffffU));
	}

	layout(set = 1, binding = 0) uniform UBO
	{
		float ubotime;
		uint uboframe;
	} ubo;

	layout(set = 1, binding = 1) uniform SceneData
	{
		Quadric		quadrics[OBJECT_MAX];
		Cube		cubes[OBJECT_MAX];
		Torus		torus[OBJECT_MAX];
		Capsule		capsules[OBJECT_MAX];
		Light		lights[OBJECT_MAX];
		int			quadricCount;
		int			cubeCount;
		int			torusCount;
		int			capsuleCount;
		int			lightCount;
		int			mobius;
		int			motionBlur;
		vec3		sunDir;
		vec3		ambientLightColor;
	} scene;

	layout(set = 1, binding = 2) uniform CamData
	{
		vec3 pos;
		vec3 fw;
		vec3 right;
		vec3 up;
		int pad;
		int	filterID;
		float fov;
		float focalLength;
		float aperture;
		int picasso;
		int swirl;
	} cam;

	layout(set = 2, binding = 0) buffer Accum
	{
		vec4 data[];
	} acc;

#endif
