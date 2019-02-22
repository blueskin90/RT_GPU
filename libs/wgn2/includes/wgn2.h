#ifndef WGN2_H
# define WGN2_H

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdint.h>

GLFWwindow *Initialize(uint32_t x, uint32_t y);
void AddUniformBuffer(uint32_t size);
void AddStorageBuffer(uint32_t size);
void AddRenderTexture(uint32_t width, uint32_t height);
void AddTextureFromData(uint32_t width, uint32_t height, void *data);
int AddTextureFromPath(char *path);
void BindComputeData();
void AddComputePipe(const char *shader);
void SetUpGraphicsPipe(const char *vertexShader, const char *fragmentShader);
void MapMemory();
void UnmapMemory();
void DrawFrame();
void UpdateBuffer(uint32_t index, void *data);
void SetWindowTitle(char *s, ...);
void Sync();
uint8_t *GetBuffer(uint32_t index, uint32_t width, uint32_t height);
void DispatchComputeShader(uint32_t index);

#endif
