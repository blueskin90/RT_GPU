/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaulaus <apaulaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:10:17 by dibarqui          #+#    #+#             */
/*   Updated: 2019/02/17 15:57:10 by apaulaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void	save_image(GLFWwindow *wnd)
{
	uint8_t *pixels;

	if (glfwGetKey(wnd, GLFW_KEY_HOME))
	{
		pixels = GetBuffer(0, 800, 800);
		stbi_write_png("./t.png", 800, 800, 4, pixels, 0);
		free(pixels);
	}
}

void	add_buffers(void)
{
	AddUniformBuffer(sizeof(t_uniform_buffer_object));
	AddUniformBuffer(sizeof(t_scene));
	AddUniformBuffer(sizeof(t_cam));
	AddStorageBuffer(1600 * 1600 * 4 * sizeof(float));
	AddRenderTexture(1600, 1600);
	if (!AddTextureFromPath("textures/0.png"))
		exit(0);
	if (!AddTextureFromPath("textures/1.png"))
		exit(0);
	if (!AddTextureFromPath("textures/2.png"))
		exit(0);
	if (!AddTextureFromPath("textures/3.png"))
		exit(0);
	if (!AddTextureFromPath("textures/4.png"))
		exit(0);
	if (!AddTextureFromPath("textures/5.png"))
		exit(0);
	if (!AddTextureFromPath("textures/6.png"))
		exit(0);
	if (!AddTextureFromPath("textures/7.png"))
		exit(0);
}

int		main(int ac, char **av)
{
	t_huge		data;
	GLFWwindow	*wnd;

	if (ac != 2)
	{
		ft_printf("usage: RT scene_file\n");
		exit(1);
	}
	wnd = Initialize(1600, 1600);
	add_buffers();
	BindComputeData();
	AddComputePipe("objs/vulkan/comp.spv");
	SetUpGraphicsPipe("objs/vulkan/vert.spv", "objs/vulkan/frag.spv");
	MapMemory();
	loop(wnd, av[1], &data, NULL);
	UnmapMemory();
}
