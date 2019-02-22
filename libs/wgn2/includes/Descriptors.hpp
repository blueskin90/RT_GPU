#ifndef DESCRIPTORS
	#define DESCRIPTORS

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
// Inlcude vulkan only

struct SetCreateParams
{
	//	Common
	VkDescriptorType dType;
	uint32_t dstBinding;
	uint32_t dSetIndex;

	//	Uniform Buffer
	VkDescriptorBufferInfo bufferInfo;

	//	RenderTexture
	VkDescriptorImageInfo imageInfo;
};

VkDescriptorSetLayout CreateDescriptorSetLayout(VkDevice device, VkDescriptorType descriptorType, VkShaderStageFlags stageFlags, uint32_t *bindings, uint32_t bindingCount);
VkDescriptorSet *CreateDesciptorSets(VkDevice device, VkDescriptorSetLayout *dSetLayouts, uint32_t dSetCount, VkDescriptorPool dPool, uint32_t paramCount, SetCreateParams *params);

#endif
