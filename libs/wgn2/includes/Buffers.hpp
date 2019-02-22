#ifndef BUFFERS
	#define BUFFERS

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
// Inlcude vulkan only

struct Buffer
{
	VkBuffer buff;
	VkDeviceMemory buffMem;
	VkDeviceSize size;
	void *data;
	// uint32_t binding;
};

Buffer CreateDataBuffer(VkDevice device, VkPhysicalDevice gpu, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);

#endif
