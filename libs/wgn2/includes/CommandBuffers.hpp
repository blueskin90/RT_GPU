#ifndef COMMAND_BUFFERS
	#define COMMAND_BUFFERS

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
// Inlcude vulkan only

struct RecorderParams
{
	//	Compute
	uint32_t xGroupSize;
	uint32_t yGroupSize;
	uint32_t zGroupSize;

	//	Graphics
	VkRenderPass renderPass;
	VkFramebuffer frameBuffer;
	VkExtent2D extent;
};

VkCommandBuffer AllocateCommandBuffer(VkDevice device, VkCommandPool cmdPool);
VkCommandBuffer BeginTemporaryCmdBuffer(VkDevice device, VkCommandPool cmdPool);
void EndTemporaryCmdBuffer(VkDevice device, VkCommandPool cmdPool, VkQueue queue, VkCommandBuffer commandBuffer);
void RecordCommandBuffer(VkCommandBuffer cmdBuff, VkPipeline pipe, VkPipelineLayout pipeLayout, VkDescriptorSet *dSets,
							uint32_t dSetsCount, VkPipelineBindPoint bindPoint, RecorderParams params);

#endif
