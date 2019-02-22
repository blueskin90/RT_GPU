#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
// Inlcude vulkan only

VkShaderModule GetShaderModule(VkDevice device, const char *path);
