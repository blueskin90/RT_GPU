
#include <cstdlib>
#include <cstring>

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <vector>

#include "RenderTexture.hpp"
#include "Descriptors.hpp"
#include "Shaders.hpp"
#include "Buffers.hpp"


#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))


#define GET_INSTANCE_PROC_ADDR(inst, entrypoint)								\
        demo->fp##entrypoint = 													\
            (PFN_vk##entrypoint)vkGetInstanceProcAddr(inst, "vk" #entrypoint);

#define GET_DEVICE_PROC_ADDR(dev, entrypoint)                                  \
        demo->fp##entrypoint =                                                 \
            (PFN_vk##entrypoint)vkGetDeviceProcAddr(dev, "vk" #entrypoint);

typedef struct
{
    VkImage image;
    VkCommandBuffer cmd;
    VkImageView view;
} SwapchainBuffers;


struct demo
{
    GLFWwindow* window;
    VkSurfaceKHR surface;

    VkInstance inst;
    VkPhysicalDevice gpu;
    VkDevice device;
    VkQueue queue;

    VkPhysicalDeviceProperties gpuProps;
    VkPhysicalDeviceFeatures gpuFeatures;
    VkQueueFamilyProperties *queueProps;
    uint32_t graphicsQueueIndex;

    uint32_t enabledExtensionCount;
    const char *extensionNames[64];

    int width, height;
    VkFormat format;
    VkColorSpaceKHR colorSpace;

    PFN_vkGetPhysicalDeviceSurfaceSupportKHR
        fpGetPhysicalDeviceSurfaceSupportKHR;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR
        fpGetPhysicalDeviceSurfaceCapabilitiesKHR;
    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR
        fpGetPhysicalDeviceSurfaceFormatsKHR;
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR
        fpGetPhysicalDeviceSurfacePresentModesKHR;
    PFN_vkCreateSwapchainKHR fpCreateSwapchainKHR;
    PFN_vkDestroySwapchainKHR fpDestroySwapchainKHR;
    PFN_vkGetSwapchainImagesKHR fpGetSwapchainImagesKHR;
    PFN_vkAcquireNextImageKHR fpAcquireNextImageKHR;
    PFN_vkQueuePresentKHR fpQueuePresentKHR;

    uint32_t swapchainImageCount;
    VkSwapchainKHR swapchain;
    SwapchainBuffers *swapChainbuffers;

    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;
    VkPipeline pipeline;

	VkExtent2D swapchainExtent;
    VkFramebuffer *framebuffers;
	VkCommandBuffer *commandBuffers;

	VkDescriptorPool descriptorPool;
	VkDescriptorSet *descriptorSets;
	// VkDescriptorSetLayout descriptorSetLayout;
	// VkDescriptorSetLayout samplerDescriptorSetLayout;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence fence;

    VkPhysicalDeviceMemoryProperties memory_properties;


	VkDescriptorSetLayout *graphicsDescriptorSetLayouts;





	VkCommandPool cmdPool;
	VkFence	computeFence;

	VkDescriptorPool computeDescriptorPool;
	VkDescriptorSetLayout *computeDescriptorSetLayouts;
	VkDescriptorSet *computeDescriptorSets;
	VkPipelineLayout computePipelineLayout;

	std::vector<Buffer> uniformBuffers;
	std::vector<Buffer> storageBuffers;
	std::vector<RenderTexture> renderTextures;
	std::vector<RenderTexture> textures;

	std::vector<VkPipeline> computePipelines;
	std::vector<VkCommandBuffer> computeCmdBuffers;

    uint32_t queueCount;
};
struct demo *demo;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void CreateWindow()
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    demo->window = glfwCreateWindow(demo->width / 2, demo->height / 2, "Test", nullptr, nullptr);
    glfwSetWindowUserPointer(demo->window, demo);
    glfwSetKeyCallback(demo->window, key_callback);
}

uint32_t validationLayerCount;
char *validationLayers;

void MoreVkInit()
{
	uint32_t requiredExtensionCount = 0;
	const char **requiredExtensions = nullptr;
    requiredExtensions = glfwGetRequiredInstanceExtensions(&requiredExtensionCount);
    for (int i = 0; i < requiredExtensionCount; i++)
        demo->extensionNames[demo->enabledExtensionCount++] = requiredExtensions[i];

    VkApplicationInfo app = {};
    app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app.pNext = nullptr;
	app.pApplicationName = "Test";
    app.applicationVersion = 0;
    app.pEngineName = "Test";
    app.engineVersion = 0;
    app.apiVersion = VK_API_VERSION_1_1;

    VkInstanceCreateInfo instanceInfo = {};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pNext = nullptr;
    instanceInfo.pApplicationInfo = &app;
    instanceInfo.enabledExtensionCount = demo->enabledExtensionCount;
    instanceInfo.ppEnabledExtensionNames = (const char *const *)demo->extensionNames;
    vkCreateInstance(&instanceInfo, nullptr, &demo->inst);

	uint32_t gpuCount;
    vkEnumeratePhysicalDevices(demo->inst, &gpuCount, nullptr);
	VkPhysicalDevice *physicalDevices = new VkPhysicalDevice[gpuCount];
    vkEnumeratePhysicalDevices(demo->inst, &gpuCount, physicalDevices);
	demo->gpu = physicalDevices[0];
    delete[] physicalDevices;

    uint32_t deviceExtensionCount = 0;
    demo->enabledExtensionCount = 0;

    vkEnumerateDeviceExtensionProperties(demo->gpu, nullptr, &deviceExtensionCount, nullptr);
	VkExtensionProperties *deviceExtensions = new VkExtensionProperties[deviceExtensionCount];
    vkEnumerateDeviceExtensionProperties(demo->gpu, nullptr, &deviceExtensionCount, deviceExtensions);

    for (int i = 0; i < deviceExtensionCount; i++)
        if (!strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME,deviceExtensions[i].extensionName))
            demo->extensionNames[demo->enabledExtensionCount++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
    delete[] deviceExtensions;

    GET_INSTANCE_PROC_ADDR(demo->inst, GetPhysicalDeviceSurfaceCapabilitiesKHR);
    GET_INSTANCE_PROC_ADDR(demo->inst, GetPhysicalDeviceSurfaceFormatsKHR);
    GET_INSTANCE_PROC_ADDR(demo->inst, GetPhysicalDeviceSurfacePresentModesKHR);
    GET_INSTANCE_PROC_ADDR(demo->inst, GetPhysicalDeviceSurfaceSupportKHR);

    vkGetPhysicalDeviceProperties(demo->gpu, &demo->gpuProps);

    vkGetPhysicalDeviceQueueFamilyProperties(demo->gpu, &demo->queueCount, nullptr);
	demo->queueProps = new VkQueueFamilyProperties[demo->queueCount];
    vkGetPhysicalDeviceQueueFamilyProperties(demo->gpu, &demo->queueCount, demo->queueProps);
    vkGetPhysicalDeviceFeatures(demo->gpu, &demo->gpuFeatures);
}

static void InitDevice()
{
	demo->graphicsQueueIndex = 0;

    float queuePriorities[1] = {0.0};
    VkDeviceQueueCreateInfo queue = {};
    queue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue.pNext = nullptr;
    queue.queueFamilyIndex = demo->graphicsQueueIndex;
    queue.queueCount = 1;
    queue.pQueuePriorities = queuePriorities;


    VkPhysicalDeviceFeatures features = {};
    if (demo->gpuFeatures.shaderClipDistance)
        features.shaderClipDistance = VK_TRUE;

    VkDeviceCreateInfo device = {};
    device.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device.pNext = nullptr;
    device.queueCreateInfoCount = 1;
    device.pQueueCreateInfos = &queue;
    device.enabledLayerCount = 0;
    device.ppEnabledLayerNames = nullptr;
    device.enabledExtensionCount = demo->enabledExtensionCount;
    device.ppEnabledExtensionNames = (const char *const *)demo->extensionNames;
    device.pEnabledFeatures = &features;

    vkCreateDevice(demo->gpu, &device, nullptr, &demo->device);

    GET_DEVICE_PROC_ADDR(demo->device, CreateSwapchainKHR);
    GET_DEVICE_PROC_ADDR(demo->device, DestroySwapchainKHR);
    GET_DEVICE_PROC_ADDR(demo->device, GetSwapchainImagesKHR);
    GET_DEVICE_PROC_ADDR(demo->device, AcquireNextImageKHR);
    GET_DEVICE_PROC_ADDR(demo->device, QueuePresentKHR);
}

static void InitVk()
{
    glfwCreateWindowSurface(demo->inst, demo->window, nullptr, &demo->surface);

    vkGetDeviceQueue(demo->device, demo->graphicsQueueIndex, 0, &demo->queue);

    uint32_t formatCount;
    demo->fpGetPhysicalDeviceSurfaceFormatsKHR(demo->gpu, demo->surface, &formatCount, nullptr);
	VkSurfaceFormatKHR *surfFormats = new VkSurfaceFormatKHR[formatCount];
    demo->fpGetPhysicalDeviceSurfaceFormatsKHR(demo->gpu, demo->surface, &formatCount, surfFormats);

    demo->format = surfFormats[2].format;
    demo->colorSpace = surfFormats[2].colorSpace;
	delete[] surfFormats;
    vkGetPhysicalDeviceMemoryProperties(demo->gpu, &demo->memory_properties);
}

static void cleanup(int resize)
{
    for (int i = 0; i < demo->swapchainImageCount; i++)
        vkDestroyFramebuffer(demo->device, demo->framebuffers[i], nullptr);
    free(demo->framebuffers);

    vkDestroyCommandPool(demo->device, demo->cmdPool, nullptr);

    vkDestroyPipeline(demo->device, demo->pipeline, nullptr);
    vkDestroyRenderPass(demo->device, demo->renderPass, nullptr);
    vkDestroyPipelineLayout(demo->device, demo->pipelineLayout, nullptr);


    for (int i = 0; i < demo->swapchainImageCount; i++)
        vkDestroyImageView(demo->device, demo->swapChainbuffers[i].view, nullptr);

    demo->fpDestroySwapchainKHR(demo->device, demo->swapchain, nullptr);
    free(demo->swapChainbuffers);

	vkDestroySemaphore(demo->device, demo->imageAvailableSemaphore, nullptr);
	vkDestroySemaphore(demo->device, demo->renderFinishedSemaphore, nullptr);
	vkDestroyFence(demo->device, demo->fence, nullptr);

	// vkFreeMemory(demo->device, demo->uniformBuffers[0].buffMem, nullptr);
	// vkDestroyBuffer(demo->device, demo->uniformBuffers[0].buff, nullptr);
	// vkDestroyDescriptorSetLayout(demo->device, demo->descriptorSetLayout, nullptr);
	// vkDestroyDescriptorPool(demo->device, demo->descriptorPool, nullptr);

	// vkFreeMemory(demo->device, demo->renderTexture.mem, nullptr);
	// vkDestroyImage(demo->device, demo->renderTexture.image, nullptr);

	vkDestroyDevice(demo->device, nullptr);
	vkDestroySurfaceKHR(demo->inst, demo->surface, nullptr);
	vkDestroyInstance(demo->inst, nullptr);

	free(demo->queueProps);

	glfwDestroyWindow(demo->window);
	glfwTerminate();
}

void CreateSwapchain()
{
	VkBool32 surfaceSupport;
	vkGetPhysicalDeviceSurfaceSupportKHR(demo->gpu, 0, demo->surface, &surfaceSupport);

    VkSurfaceCapabilitiesKHR surfCapabilities;
    demo->fpGetPhysicalDeviceSurfaceCapabilitiesKHR( demo->gpu, demo->surface, &surfCapabilities);

    demo->swapchainExtent.width = demo->width;
    demo->swapchainExtent.height = demo->height;

    VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;

    uint32_t desiredNumOfSwapchainImages = surfCapabilities.minImageCount;

	VkSurfaceTransformFlagBitsKHR preTransform;
    preTransform = surfCapabilities.currentTransform;

    VkSwapchainCreateInfoKHR swapchain = {};
    swapchain.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain.pNext = nullptr;
    swapchain.surface = demo->surface;
    swapchain.minImageCount = desiredNumOfSwapchainImages;
    swapchain.imageFormat = demo->format;
    swapchain.imageColorSpace = demo->colorSpace;
    swapchain.imageExtent = demo->swapchainExtent;
    swapchain.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchain.preTransform = preTransform;
    swapchain.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain.imageArrayLayers = 1;
    swapchain.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchain.queueFamilyIndexCount = 0;
    swapchain.pQueueFamilyIndices = nullptr;
    swapchain.presentMode = swapchainPresentMode;
    swapchain.oldSwapchain = VK_NULL_HANDLE;
    swapchain.clipped = true;

    demo->fpCreateSwapchainKHR(demo->device, &swapchain, nullptr, &demo->swapchain);

	demo->fpGetSwapchainImagesKHR(demo->device, demo->swapchain, &demo->swapchainImageCount, nullptr);
    VkImage *swapchainImages = new VkImage[demo->swapchainImageCount];
    demo->fpGetSwapchainImagesKHR(demo->device, demo->swapchain, &demo->swapchainImageCount, swapchainImages);
    demo->swapChainbuffers = new SwapchainBuffers[demo->swapchainImageCount];

    for (int i = 0; i < demo->swapchainImageCount; i++)
	{
        VkImageViewCreateInfo imageInfo = {};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageInfo.pNext = nullptr;
        imageInfo.format = demo->format;

        imageInfo.components.r = VK_COMPONENT_SWIZZLE_R;
		imageInfo.components.g = VK_COMPONENT_SWIZZLE_G;
		imageInfo.components.b = VK_COMPONENT_SWIZZLE_B;
		imageInfo.components.a = VK_COMPONENT_SWIZZLE_A;

        imageInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
       	imageInfo.subresourceRange.baseMipLevel = 0;
        imageInfo.subresourceRange.levelCount = 1;
        imageInfo.subresourceRange.baseArrayLayer = 0;
        imageInfo.subresourceRange.layerCount = 1;

        imageInfo.viewType = VK_IMAGE_VIEW_TYPE_2D,
        imageInfo.flags = 0,

        demo->swapChainbuffers[i].image = swapchainImages[i];

        imageInfo.image = demo->swapChainbuffers[i].image;

        vkCreateImageView(demo->device, &imageInfo, nullptr, &demo->swapChainbuffers[i].view);
    }
	delete[] swapchainImages;
}

void CreateRenderPass()
{
	VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = demo->format;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;
	vkCreateRenderPass(demo->device, &renderPassInfo, nullptr, &demo->renderPass);
}

void CreateGraphicsPipe(const char *vertexShaderPath, const char *fragmentShaderPath)
{
	VkShaderModule vertexShader = GetShaderModule(demo->device, vertexShaderPath);
	VkShaderModule fragmentShader = GetShaderModule(demo->device, fragmentShaderPath);

	VkPipelineShaderStageCreateInfo shaderStages[2] = {};
	shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[0].module = vertexShader;
    shaderStages[0].pName = "main";

    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].module = fragmentShader;
    shaderStages[1].pName = "main";

	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 0;
	vertexInputInfo.pVertexBindingDescriptions = nullptr;
	vertexInputInfo.vertexAttributeDescriptionCount = 0;
	vertexInputInfo.pVertexAttributeDescriptions = nullptr;

	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)demo->width;
	viewport.height = (float)demo->height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = {};
	scissor.offset.x = 0;
	scissor.offset.y = 0;
	scissor.extent = demo->swapchainExtent;

	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	VkPipelineRasterizationStateCreateInfo rasterizer = {};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling = {};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;

	VkPipelineColorBlendStateCreateInfo colorBlending = {};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;

	VkDynamicState dynamicStates[] = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_LINE_WIDTH
	};

	VkPipelineDynamicStateCreateInfo dynamicState = {};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = 0; //2
	dynamicState.pDynamicStates = dynamicStates;

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 2;
	pipelineLayoutInfo.pSetLayouts = demo->graphicsDescriptorSetLayouts;
	vkCreatePipelineLayout(demo->device, &pipelineLayoutInfo, nullptr, &demo->pipelineLayout);

	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;

	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = nullptr;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = &dynamicState;
	pipelineInfo.layout = demo->pipelineLayout;
	pipelineInfo.renderPass = demo->renderPass;
	pipelineInfo.subpass = 0;
	vkCreateGraphicsPipelines(demo->device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &demo->pipeline);

	vkDestroyShaderModule(demo->device, fragmentShader, nullptr);
    vkDestroyShaderModule(demo->device, vertexShader, nullptr);
}

void CreateFrameBuffers()
{
	demo->framebuffers = new VkFramebuffer[demo->swapchainImageCount];
	VkImageView *tmp = new VkImageView[demo->swapchainImageCount];
	for (int i = 0; i < demo->swapchainImageCount; ++i)
		tmp[i] = demo->swapChainbuffers[i].view;
	for (int i = 0; i < demo->swapchainImageCount; ++i)
	{
		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = demo->renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = &tmp[i];
		framebufferInfo.width = demo->width;
		framebufferInfo.height = demo->height;
		framebufferInfo.layers = 1;

		vkCreateFramebuffer(demo->device, &framebufferInfo, nullptr, &demo->framebuffers[i]);
	}
	delete[] tmp;
}

void CreateCommandPools()
{
	VkCommandPoolCreateInfo cmdPoolInfo = {};
	cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmdPoolInfo.queueFamilyIndex = demo->graphicsQueueIndex;
	cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	vkCreateCommandPool(demo->device, &cmdPoolInfo, nullptr, &demo->cmdPool);
}

void CreateGraphicsCommandBuffers()
{
	demo->commandBuffers = new VkCommandBuffer[demo->swapchainImageCount];
	for (int i = 0; i < demo->swapchainImageCount; ++i)
	{
		demo->commandBuffers[i] = AllocateCommandBuffer(demo->device, demo->cmdPool);

		RecorderParams params;
		params.renderPass = demo->renderPass;
		params.frameBuffer = demo->framebuffers[i];
		params.extent = demo->swapchainExtent;
		RecordCommandBuffer(demo->commandBuffers[i], demo->pipeline, demo->pipelineLayout, demo->descriptorSets, 2, VK_PIPELINE_BIND_POINT_GRAPHICS, params);
	}
}

void CreateSemaphores()
{
	VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	vkCreateSemaphore(demo->device, &semaphoreInfo, nullptr, &demo->imageAvailableSemaphore);
    vkCreateSemaphore(demo->device, &semaphoreInfo, nullptr, &demo->renderFinishedSemaphore);

	VkFenceCreateInfo fenceInfo = {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	vkCreateFence(demo->device, &fenceInfo, nullptr, &demo->fence);
	vkResetFences(demo->device, 1, &demo->fence);
}

void CreateGraphicsDescriptors()
{
	// Pool
	VkDescriptorPoolSize poolSize[2] = {};
	poolSize[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSize[0].descriptorCount = 1;
	poolSize[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSize[1].descriptorCount = 1;

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = 2;
	poolInfo.pPoolSizes = poolSize;
	poolInfo.maxSets = 2;
	vkCreateDescriptorPool(demo->device, &poolInfo, nullptr, &demo->descriptorPool);

	// Layouts
	demo->graphicsDescriptorSetLayouts = new VkDescriptorSetLayout[2];

	uint32_t bufferBindings[1] = { 0 };
	demo->graphicsDescriptorSetLayouts[0] = CreateDescriptorSetLayout(demo->device, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, &bufferBindings[0], 1);
	uint32_t textureBindingd[2] = { 0 };
	demo->graphicsDescriptorSetLayouts[1]  = CreateDescriptorSetLayout(demo->device, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, &textureBindingd[0], 1);

	VkDescriptorBufferInfo bufferInfo = {};
	bufferInfo.buffer = demo->uniformBuffers[0].buff;
	bufferInfo.offset = 0;
	bufferInfo.range = demo->uniformBuffers[0].size;

	SetCreateParams *params = new SetCreateParams[3];
	params[0].dType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	params[0].dstBinding = 0;
	params[0].bufferInfo = bufferInfo;
	params[0].dSetIndex = 0;

	params[1].dType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	params[1].dstBinding = 0;
	params[1].imageInfo = demo->renderTextures[0].descriptor;
	params[1].dSetIndex = 1;

	demo->descriptorSets = CreateDesciptorSets(demo->device, demo->graphicsDescriptorSetLayouts, 2, demo->descriptorPool, 2, params);
	delete[] params;
}

VkPipeline CreateComputePipe(const char *shader)
{
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.pNext = nullptr;
	pipelineLayoutInfo.flags = 0;
	pipelineLayoutInfo.setLayoutCount = 4;
	pipelineLayoutInfo.pSetLayouts = demo->computeDescriptorSetLayouts;
	vkCreatePipelineLayout(demo->device, &pipelineLayoutInfo, nullptr, &demo->computePipelineLayout);

	VkSpecializationInfo dafuq = {};

	VkShaderModule computeShader = GetShaderModule(demo->device, shader);
	VkPipelineShaderStageCreateInfo computeShaderStage;
	computeShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	computeShaderStage.pNext = nullptr;
	computeShaderStage.flags = 0;
    computeShaderStage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    computeShaderStage.module = computeShader;
    computeShaderStage.pName = "main";
	computeShaderStage.pSpecializationInfo = &dafuq;

	VkComputePipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
	pipelineInfo.pNext = nullptr;
	pipelineInfo.flags = 0;
	pipelineInfo.stage = computeShaderStage;
	pipelineInfo.layout = demo->computePipelineLayout;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
	pipelineInfo.basePipelineIndex = -1;

	VkPipeline pipeline;
	vkCreateComputePipelines(demo->device, nullptr, 1, &pipelineInfo, nullptr, &pipeline);
	vkDestroyShaderModule(demo->device, computeShader, nullptr);
	return pipeline;
}

VkCommandBuffer CreateComputeCommandBuffer(VkPipeline pipeline)
{
	VkCommandBuffer cmdBuff = AllocateCommandBuffer(demo->device, demo->cmdPool);

	RecorderParams params;
	params.xGroupSize = demo->width / 16;
	params.yGroupSize = demo->height / 16;
	params.zGroupSize = 1;
	RecordCommandBuffer(cmdBuff, pipeline, demo->computePipelineLayout, demo->computeDescriptorSets, 4, VK_PIPELINE_BIND_POINT_COMPUTE, params);
	return cmdBuff;
}

void desc(VkDescriptorSetLayout *layouts, VkDescriptorPool *dPool, VkShaderStageFlagBits stage)
{
	// Pool
	VkDescriptorPoolSize poolSize[4] = {};
	poolSize[0].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
	poolSize[0].descriptorCount = demo->renderTextures.size();
	poolSize[1].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSize[1].descriptorCount = demo->uniformBuffers.size();
	poolSize[2].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	poolSize[2].descriptorCount = demo->storageBuffers.size();
	poolSize[3].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSize[3].descriptorCount = demo->textures.size();

	VkDescriptorPoolCreateInfo descriptorPoolInfo = {};
	descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	descriptorPoolInfo.maxSets = 4;
	descriptorPoolInfo.poolSizeCount = 4;
	descriptorPoolInfo.pPoolSizes =	poolSize;
	vkCreateDescriptorPool(demo->device, &descriptorPoolInfo, nullptr, dPool);

	// Layouts
	uint32_t *renderTextureBindings = new uint32_t[demo->renderTextures.size()];
	for (uint32_t i = 0; i < demo->renderTextures.size(); ++i)
		renderTextureBindings[i] = i;
	layouts[0] = CreateDescriptorSetLayout(demo->device, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, stage, renderTextureBindings, demo->renderTextures.size());
	delete[] renderTextureBindings;

	uint32_t *uniformBufferBindings = new uint32_t[demo->uniformBuffers.size()];
	for (uint32_t i = 0; i < demo->uniformBuffers.size(); ++i)
		uniformBufferBindings[i] = i;
	layouts[1] = CreateDescriptorSetLayout(demo->device, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, stage, uniformBufferBindings, demo->uniformBuffers.size());
	delete[] uniformBufferBindings;

	uint32_t *storageBufferBindings = new uint32_t[demo->storageBuffers.size()];
	for (uint32_t i = 0; i < demo->storageBuffers.size(); ++i)
		storageBufferBindings[i] = i;
	layouts[2] = CreateDescriptorSetLayout(demo->device, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, stage, storageBufferBindings, demo->storageBuffers.size());
	delete[] storageBufferBindings;

	uint32_t *textureBindings = new uint32_t[demo->textures.size()];
	for (uint32_t i = 0; i < demo->textures.size(); ++i)
		textureBindings[i] = i;
	layouts[3] = CreateDescriptorSetLayout(demo->device, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, stage, textureBindings, demo->textures.size());
	delete[] textureBindings;

	// Sets
	SetCreateParams *params = new SetCreateParams[demo->renderTextures.size() + demo->uniformBuffers.size() + demo->storageBuffers.size() + demo->textures.size()];

	uint32_t gIndex = 0;
	for (uint32_t i = 0; i < demo->renderTextures.size(); ++i)
	{
		params[gIndex].dType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
		params[gIndex].dstBinding = i;
		params[gIndex].imageInfo = demo->renderTextures[i].descriptor;
		params[gIndex].dSetIndex = 0;
		gIndex++;
	}

	for (uint32_t i = 0; i < demo->uniformBuffers.size(); ++i)
	{
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = demo->uniformBuffers[i].buff;
		bufferInfo.offset = 0;
		bufferInfo.range = demo->uniformBuffers[i].size;

		params[gIndex].dType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		params[gIndex].dstBinding = i;
		params[gIndex].bufferInfo = bufferInfo;
		params[gIndex].dSetIndex = 1;
		gIndex++;
	}

	for (uint32_t i = 0; i < demo->storageBuffers.size(); ++i)
	{
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = demo->storageBuffers[i].buff;
		bufferInfo.offset = 0;
		bufferInfo.range = demo->storageBuffers[i].size;

		params[gIndex].dType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		params[gIndex].dstBinding = i;
		params[gIndex].bufferInfo = bufferInfo;
		params[gIndex].dSetIndex = 2;
		gIndex++;
	}

	for (uint32_t i = 0; i < demo->textures.size(); ++i)
	{
		demo->textures[i].descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		params[gIndex].dType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		params[gIndex].dstBinding = i;
		params[gIndex].imageInfo = demo->textures[i].descriptor;
		params[gIndex].dSetIndex = 3;
		gIndex++;
	}

	demo->computeDescriptorSets = CreateDesciptorSets(demo->device, layouts, 4, *dPool, gIndex, params);
	delete[] params;
}

extern "C" GLFWwindow *Initialize(uint32_t x, uint32_t y);
GLFWwindow *Initialize(uint32_t x, uint32_t y)
{
	demo = (struct demo*)calloc(1, sizeof(struct demo));

	demo->width = x;
    demo->height = y;

	glfwInit();
	CreateWindow();

    MoreVkInit();
	InitDevice();
	InitVk();
	CreateSwapchain();
	CreateRenderPass();
	CreateCommandPools();

	VkFenceCreateInfo fenceCreateInfo = {};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	vkCreateFence(demo->device, &fenceCreateInfo, nullptr, &demo->computeFence);

	return demo->window;
}

extern "C" void AddUniformBuffer(uint32_t size);
void AddUniformBuffer(uint32_t size)
{
	VkDeviceSize bufferSize = size;
	Buffer tmp = CreateDataBuffer(demo->device, demo->gpu, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	demo->uniformBuffers.push_back(tmp);
}

extern "C" void AddStorageBuffer(uint32_t size);
void AddStorageBuffer(uint32_t size)
{
	VkDeviceSize bufferSize = size;
	Buffer tmp = CreateDataBuffer(demo->device, demo->gpu, bufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT/*VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT*/);
	demo->storageBuffers.push_back(tmp);
}

extern "C" void AddRenderTexture(uint32_t width, uint32_t height);
void AddRenderTexture(uint32_t width, uint32_t height)
{
	RenderTexture texture = CreateRenderTexture(width, height, VK_FORMAT_R16G16B16A16_SFLOAT, demo->device, demo->cmdPool, demo->queue, demo->gpu);
	demo->renderTextures.push_back(texture);
}

extern "C" void AddTextureFromData(uint32_t width, uint32_t height, void *data);
void AddTextureFromData(uint32_t width, uint32_t height, void *data)
{
	RenderTexture texture = CreateTestTexture(width, height, VK_FORMAT_R8G8B8A8_UNORM, demo->device, demo->cmdPool, demo->queue, demo->gpu);
	demo->textures.push_back(texture);

	VkDeviceSize size = width * height * sizeof(uint8_t) * 4;
	Buffer fuck = CreateDataBuffer(demo->device, demo->gpu, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	vkMapMemory(demo->device, fuck.buffMem, 0, fuck.size, 0, &fuck.data);
		memcpy(fuck.data, data, fuck.size);
	vkUnmapMemory(demo->device, fuck.buffMem);

	VkCommandBuffer tmp = BeginTemporaryCmdBuffer(demo->device, demo->cmdPool);
		VkBufferImageCopy region = {};
		region.bufferOffset = 0;
		region.bufferRowLength = 0;
		region.bufferImageHeight = 0;

		region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.mipLevel = 0;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount = 1;

		region.imageOffset.x = 0;
		region.imageOffset.y = 0;
		region.imageOffset.z = 0;
		region.imageExtent.width = width;
		region.imageExtent.height = height;
		region.imageExtent.depth = 1;

		vkCmdCopyBufferToImage(tmp, fuck.buff, texture.image, VK_IMAGE_LAYOUT_GENERAL, 1, &region);
	EndTemporaryCmdBuffer(demo->device, demo->cmdPool, demo->queue, tmp);
}

extern "C" int AddTextureFromPath(char *path);
int AddTextureFromPath(char *path)
{
	int texWidth, texHeight, texChannels;
    unsigned char *data = stbi_load(path, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	if (!data || (texHeight * texWidth) > 1024 * 1024)
		return 0;

	RenderTexture texture = CreateTestTexture(texWidth, texHeight, VK_FORMAT_R8G8B8A8_UNORM, demo->device, demo->cmdPool, demo->queue, demo->gpu);
	demo->textures.push_back(texture);

	VkDeviceSize size = texWidth * texHeight * sizeof(uint8_t) * 4;
	Buffer tmpBuff = CreateDataBuffer(demo->device, demo->gpu, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	vkMapMemory(demo->device, tmpBuff.buffMem, 0, tmpBuff.size, 0, &tmpBuff.data);
		memcpy(tmpBuff.data, data, tmpBuff.size);
	vkUnmapMemory(demo->device, tmpBuff.buffMem);
	free(data);

	VkCommandBuffer tmp = BeginTemporaryCmdBuffer(demo->device, demo->cmdPool);
		VkBufferImageCopy region = {};
		region.bufferOffset = 0;
		region.bufferRowLength = 0;
		region.bufferImageHeight = 0;

		region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.mipLevel = 0;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount = 1;

		region.imageOffset.x = 0;
		region.imageOffset.y = 0;
		region.imageOffset.z = 0;
		region.imageExtent.width = texWidth;
		region.imageExtent.height = texHeight;
		region.imageExtent.depth = 1;
		vkCmdCopyBufferToImage(tmp, tmpBuff.buff, texture.image, VK_IMAGE_LAYOUT_GENERAL, 1, &region);
	EndTemporaryCmdBuffer(demo->device, demo->cmdPool, demo->queue, tmp);
	return 1;
}

extern "C" uint8_t *GetBuffer(uint32_t index, uint32_t width, uint32_t height);
uint8_t *GetBuffer(uint32_t index, uint32_t width, uint32_t height)
{

	Buffer tmpBuff = CreateDataBuffer(demo->device, demo->gpu, demo->storageBuffers[index].size, VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	VkCommandBuffer tmp = BeginTemporaryCmdBuffer(demo->device, demo->cmdPool);
		VkBufferCopy region = {};
		region.dstOffset = 0;
		region.srcOffset = 0;
		region.size = demo->storageBuffers[index].size;
		vkCmdCopyBuffer(tmp, demo->storageBuffers[index].buff, tmpBuff.buff, 1, &region);
	EndTemporaryCmdBuffer(demo->device, demo->cmdPool, demo->queue, tmp);

	vkMapMemory(demo->device, tmpBuff.buffMem, 0, tmpBuff.size, 0, &tmpBuff.data);
		float *raw = new float[width * height * 4];
		memcpy(raw, tmpBuff.data, tmpBuff.size);
		uint8_t *pixels = (uint8_t *)malloc(800 * 800 * 4 * sizeof(uint8_t));

		uint32_t gI = 0;
		for (uint32_t i = 0; i < width; i++)
		{
			for (uint32_t j = 0; j < height; j++)
			{
				for (uint32_t k = 0; k < 4; k++)
				{
					uint32_t tt = j * 4 + (width - 1 - i) * width * 4 + k;
					raw[tt] = pow(raw[tt], 1.0 / 2.2);
					uint8_t c = ((raw[tt] > 1.0) ? 255 : raw[tt] * 255);
					pixels[gI] = c;
					gI++;
				}
			}
		}
		delete[] raw;
	vkUnmapMemory(demo->device, tmpBuff.buffMem);
	return pixels;
}

extern "C" void BindComputeData();
void BindComputeData()
{
	demo->computeDescriptorSetLayouts = new VkDescriptorSetLayout[4];
	desc(demo->computeDescriptorSetLayouts, &demo->computeDescriptorPool, VK_SHADER_STAGE_COMPUTE_BIT);
}

extern "C" void AddComputePipe(const char *shader);
void AddComputePipe(const char *shader)
{
	demo->computePipelines.push_back(CreateComputePipe(shader));
	demo->computeCmdBuffers.push_back(CreateComputeCommandBuffer(demo->computePipelines[demo->computePipelines.size() - 1]));
}

extern "C" void SetUpGraphicsPipe(const char *vertexShader, const char *fragmentShader);
void SetUpGraphicsPipe(const char *vertexShader, const char *fragmentShader)
{
	CreateGraphicsDescriptors();
	CreateGraphicsPipe(vertexShader, fragmentShader);
	CreateFrameBuffers();
	CreateGraphicsCommandBuffers();
	CreateSemaphores();
}

extern "C" void MapMemory();
void MapMemory()
{
	for (uint32_t i = 0; i < demo->uniformBuffers.size(); ++i)
		vkMapMemory(demo->device, demo->uniformBuffers[i].buffMem, 0, demo->uniformBuffers[i].size, 0, &demo->uniformBuffers[i].data);
}

extern "C" void UnmapMemory();
void UnmapMemory()
{
	for (uint32_t i = 0; i < demo->uniformBuffers.size(); ++i)
		vkUnmapMemory(demo->device, demo->uniformBuffers[i].buffMem);
}

extern "C" void DispatchComputeShader(uint32_t index)
{
	VkSubmitInfo computeSubmitInfo = {};
	computeSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	computeSubmitInfo.commandBufferCount = 1;

	computeSubmitInfo.pCommandBuffers = &demo->computeCmdBuffers[index];
	vkQueueSubmit(demo->queue, 1, &computeSubmitInfo, demo->computeFence);

	vkWaitForFences(demo->device, 1, &demo->computeFence, VK_TRUE, UINT64_MAX);
	vkResetFences(demo->device, 1, &demo->computeFence);
}

extern "C" void DrawFrame();
void DrawFrame()
{
	uint32_t imageIndex;
    vkAcquireNextImageKHR(demo->device, demo->swapchain, UINT64_MAX,
		demo->imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &demo->imageAvailableSemaphore;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &demo->commandBuffers[imageIndex];
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &demo->renderFinishedSemaphore;
	vkQueueSubmit(demo->queue, 1, &submitInfo, demo->fence);

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &demo->renderFinishedSemaphore;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &demo->swapchain;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr;
	vkQueuePresentKHR(demo->queue, &presentInfo);
}

extern "C" void UpdateBuffer(uint32_t index, void *data);
void UpdateBuffer(uint32_t index, void *data)
{
	memcpy(demo->uniformBuffers[index].data, data, demo->uniformBuffers[index].size);
}

#include <stdarg.h>
extern "C" void SetWindowTitle(char *s, ...);
void SetWindowTitle(char *s, ...)
{
	char *c = new char[9999];

    va_list argptr;
    va_start(argptr, s);
    	vsprintf(c, s, argptr);
		glfwSetWindowTitle(demo->window, c);
    va_end(argptr);
	delete[] c;
}

extern "C" void Sync();
void Sync()
{
	vkWaitForFences(demo->device, 1, &demo->fence, VK_TRUE, INT32_MAX);
	vkResetFences(demo->device, 1, &demo->fence);
}
