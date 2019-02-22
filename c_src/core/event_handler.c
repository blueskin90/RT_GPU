/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaulaus <apaulaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 08:47:27 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/17 15:35:56 by apaulaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		move(GLFWwindow *wnd, float delta, t_cam *cam, t_huge *data)
{
	if (glfwGetKey(wnd, GLFW_KEY_D))
		data->r = 1.0;
	else if (glfwGetKey(wnd, GLFW_KEY_A))
		data->r = -1.0;
	else
		data->r = 0.0;
	if (glfwGetKey(wnd, GLFW_KEY_W))
		data->f = 1.0;
	else if (glfwGetKey(wnd, GLFW_KEY_S))
		data->f = -1.0;
	else
		data->f = 0.0;
	if (glfwGetKey(wnd, GLFW_KEY_SPACE))
		data->u = 1.0;
	else if (glfwGetKey(wnd, GLFW_KEY_LEFT_SHIFT))
		data->u = -1.0;
	else
		data->u = 0.0;
	glfwGetCursorPos(wnd, &data->xpos, &data->ypos);
	functional_function(data, delta, cam);
	if (data->r != 0 || data->f != 0
		|| data->xdelta != 0 || data->ydelta != 0 || data->u != 0)
		return (1);
	return (0);
}

void	handle_events(GLFWwindow *wnd, char *path, t_huge *data,
					t_scenes **scenes)
{
	glfwPollEvents();
	check_mobius(wnd, data, (*scenes));
	check_blur(wnd, data, (*scenes));
	check_mouse(wnd, data);
	if (glfwGetKey(wnd, GLFW_KEY_T))
	{
		data->frame = 0;
		sphere_torus((*scenes)->scene + data->current_scene);
	}
	check_hot(path, data, scenes);
	if (change_scene(wnd, *scenes, data))
		data->frame = 0;
}

int		change_scene(GLFWwindow *wnd, t_scenes *scenes, t_huge *data)
{
	data->tmp = 0;
	if (glfwGetKey(wnd, GLFW_KEY_LEFT_BRACKET))
		data->tmp = -1;
	if (glfwGetKey(wnd, GLFW_KEY_RIGHT_BRACKET))
		data->tmp = 1;
	if (data->tmp != 0 && data->wait_time >= 0.3)
	{
		nicenorm(data, scenes);
		return (1);
	}
	if (glfwGetKey(wnd, GLFW_KEY_J))
		data->tmp = -1;
	if (glfwGetKey(wnd, GLFW_KEY_K))
		data->tmp = 1;
	if (data->tmp != 0 && data->wait_time >= 0.3)
	{
		nicenorm0(data, scenes);
		return (1);
	}
	return (0);
}

void	loop(GLFWwindow *wnd, char *path, t_huge *data, t_scenes *scenes)
{
	float		current_time;
	char		*file;

	init_loop(data);
	file = ft_strrchr(path, '/');
	file = file ? file + 1 : path;
	while (!glfwWindowShouldClose(wnd))
	{
		current_time = glfwGetTime();
		handle_events(wnd, path, data, &scenes);
		if (!data->moused)
			if (move(wnd, (current_time - data->previous_time),
				&scenes->cam[data->current_scene][data->current_cam], data))
				data->frame = 0;
		update(scenes, data);
		save_image(wnd);
		SetWindowTitle("%s -- %s : camera %d -- %d%%", file,
			scenes->scene_name[data->current_scene], data->current_cam + 1,
			(int)round((1 - pow(1000.0 / 1001.0, data->frame)) * 100));
		data->time += current_time - data->previous_time;
		data->wait_time += current_time - data->previous_time;
		data->frame++;
		data->previous_time = current_time;
	}
}

void	update(t_scenes *scenes, t_huge *data)
{
	t_uniform_buffer_object test;

	test.time = data->time;
	test.frame = data->frame;
	UpdateBuffer(0, &test);
	UpdateBuffer(1, &scenes->scene[data->current_scene]);
	UpdateBuffer(2, &scenes->cam[data->current_scene][data->current_cam]);
	DispatchComputeShader(0);
	DrawFrame();
	Sync();
}
