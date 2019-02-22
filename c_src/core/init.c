/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaulaus <apaulaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 08:52:06 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/17 15:57:28 by apaulaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_cam(GLFWwindow *wnd, t_huge *data)
{
	glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(wnd, 0, 0);
	data->prevx = 0.0;
	data->prevy = 0.0;
}

void	init_material(t_quadric *q, int i, int count)
{
	q->material.color.x = cos(i / (float)count * M_PI * 2);
	q->material.color.y = sin(i / (float)count * M_PI * 2);
	q->material.color.z = 1 - (q->material.color.x + q->material.color.y);
	q->material.reflectance = 1;
	q->material.refraction_index = 1.6;
	q->material.opacity = 1;
	q->material.roughness = 1;
}

void	nicenorm(t_huge *data, t_scenes *scenes)
{
	if (data->current_scene == 0 && data->tmp == -1 && scenes->scene_count > 1)
		data->current_scene = scenes->scene_count - 1;
	else
		data->current_scene = (data->current_scene + data->tmp)
			% scenes->scene_count;
	data->wait_time = 0.0;
	data->current_cam = 0;
}

void	nicenorm0(t_huge *data, t_scenes *scenes)
{
	if (data->current_cam == 0 && data->tmp == -1
		&& scenes->cam_count[data->current_scene] > 1)
		data->current_cam = scenes->cam_count[data->current_scene] - 1;
	else
		data->current_cam = (data->current_cam + data->tmp)
			% scenes->cam_count[data->current_scene];
	data->wait_time = 0.0;
}

void	init_loop(t_huge *data)
{
	data->current_scene = 0;
	data->wait_time = 0.0;
	data->time = 0.0;
	data->frame = 0;
	data->previous_time = glfwGetTime();
	data->wehaveafuckingmobius = 0;
	data->moused = 1;
	data->blur = 0;
}
