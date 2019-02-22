#include <Buffers.hpp>
#include <RenderTexture.hpp>

Buffer CreateDataBuffer(VkDevice device, VkPhysicalDevice gpu, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
{
	Buffer buffer;
	buffer.size = size;

    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    vkCreateBuffer(device, &bufferInfo, nullptr, &buffer.buff);

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, buffer.buff, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties, gpu); //2

    vkAllocateMemory(device, &allocInfo, nullptr, &buffer.buffMem);
    vkBindBufferMemory(device, buffer.buff, buffer.buffMem, 0);

	return buffer;
}
