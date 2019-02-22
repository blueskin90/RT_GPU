#ifndef RENDER_TEXTURES
	#define RENDER_TEXTURES

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
// Inlcude vulkan only

#include <CommandBuffers.hpp>

struct RenderTexture
{
	VkSampler sampler;
	VkImage image;
	VkImageLayout imageLayout;
	VkDeviceMemory mem;
	VkImageView view;
	VkDescriptorImageInfo descriptor;
	uint32_t width, height;
};

uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice gpu);
RenderTexture CreateRenderTexture(uint32_t x, uint32_t y, VkFormat format, VkDevice device, VkCommandPool cmdPool, VkQueue queue, VkPhysicalDevice gpu);

RenderTexture CreateTestTexture(uint32_t x, uint32_t y, VkFormat format, VkDevice device, VkCommandPool cmdPool, VkQueue queue, VkPhysicalDevice gpu);

#endif
