/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 08:33:33 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 10:13:22 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_mobius(GLFWwindow *wnd, t_huge *data, t_scenes *scenes)
{
	if (glfwGetKey(wnd, GLFW_KEY_M) && !data->wehaveafuckingmobius)
	{
		data->wehaveafuckingmobius = 1;
		scenes->scene[data->current_scene].mobius = data->wehaveafuckingmobius;
		data->frame = 0;
	}
	if (glfwGetKey(wnd, GLFW_KEY_N) && data->wehaveafuckingmobius)
	{
		data->wehaveafuckingmobius = 0;
		scenes->scene[data->current_scene].mobius = data->wehaveafuckingmobius;
		data->frame = 0;
	}
}

void	check_blur(GLFWwindow *wnd, t_huge *data, t_scenes *scenes)
{
	if (glfwGetKey(wnd, GLFW_KEY_B) && !data->blur)
	{
		data->blur = 1;
		scenes->scene[data->current_scene].motion_blur = data->blur;
		data->frame = 0;
	}
	if (glfwGetKey(wnd, GLFW_KEY_V) && data->blur)
	{
		data->blur = 0;
		scenes->scene[data->current_scene].motion_blur = data->blur;
		data->frame = 0;
	}
}

void	check_mouse(GLFWwindow *wnd, t_huge *data)
{
	if (glfwGetKey(wnd, GLFW_KEY_UP) && data->moused)
	{
		data->moused = 0;
		init_cam(wnd, data);
	}
	if (glfwGetKey(wnd, GLFW_KEY_DOWN) && !data->moused)
	{
		data->moused = 1;
		glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void	check_hot(char *path, t_huge *data, t_scenes **scenes)
{
	t_elem			*json;
	struct stat		stats;
	int				i;

	if (stat(path, &stats) < 0)
		ft_error("Path does not exist \n");
	if (stats.st_mtimespec.tv_sec != data->timestamp)
	{
		data->frame = 0;
		data->timestamp = stats.st_mtimespec.tv_sec;
		json = json_parser(path);
		if (*scenes)
		{
			i = -1;
			while (++i < (*scenes)->scene_count)
			{
				if ((*scenes)->scene_name[i])
					free((*scenes)->scene_name[i]);
				(*scenes)->scene_name[i] = NULL;
			}
			free(*scenes);
		}
		*scenes = rt_parsing(json);
		wows(data, scenes);
	}
}
