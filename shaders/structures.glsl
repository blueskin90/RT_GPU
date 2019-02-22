#ifndef STRUCTS
	#define STRUCTS

struct Transform
{
	vec3		pos;
	vec4		rot;
};

struct Material
{
	vec3		color;
	float		pad;
	float		reflectance;
	float		refractionIndex;
	float		opacity;
	float		roughness;
	int			textureID;
	int			mode;
	float		shift;
	float		stretch;
};

struct Cube
{
	Transform	transform;
	Material	material;
	vec3		size;
	float		pad;
	int			subtractID;
	int			isNegative;
};

struct Torus
{
	Transform	transform;
	Material	material;
	float		major_radius;
	float		minor_radius;
};

struct Capsule
{
	Transform	transform;
	Material	material;
	float		radius;
	float		z;
};

struct Quadric
{
	Material	material;
	mat4		matrix;
	int			subtractID;
	int			isNegative;
};

struct Light
{
	vec3 color;
	vec3 pos;
};

struct Ray
{
	vec3 ro;
	vec3 rd;
};

struct Hit
{
	bool inside;
	vec3 normal;
	vec2 coords;
	Material material;
	Material insideMat;

	float tmp;
};

#endif
