#version 460
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 outColor;
layout(location = 0) in vec2 texCoord;

layout (set = 1, binding = 0) uniform sampler2D image;

layout(set = 0, binding = 0) uniform UniformBufferObject
{
	float ubotime;
	uint uboframe;
	uint t0;
} ubo;

void main()
{
	vec2 uv = texCoord; uv.y = 1.0 - uv.y;
	outColor = texture(image, uv, 0);
}
