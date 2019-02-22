/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scenes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:27:32 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 06:31:25 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		print_lights(t_temp_scenes scenes)
{
	int		i;
	int		j;

	i = 0;
	while (i < scenes.scene_count)
	{
		ft_printf("------------------------------\n");
		ft_printf("%*c %-10s %-10d\n", 5, ' ', "LIGHTS SCENE : ", i);
		ft_printf("------------------------------\n");
		j = 0;
		while (j < scenes.scene[i].light_count)
		{
			ft_printf("%*c %-10s %-10d\n", 5, ' ', "LIGHT  NUMBER : ", j);
			ft_printf("%*c %-10s : \n", 10, ' ', "color");
			print_vec3(scenes.scene[i].lights[j].color, 15);
			ft_printf("%*c %-10s : \n", 10, ' ', "position");
			print_vec3(scenes.scene[i].lights[j].pos, 15);
			j++;
		}
		i++;
	}
}

void		print_cam(t_cam cam, int cam_nbr)
{
	ft_printf("------------------------------\n");
	ft_printf("%*c %-10s %-10d\n", 5, ' ', "camera", cam_nbr);
	ft_printf("------------------------------\n");
	ft_printf("%*c %-10s : \n", 10, ' ', "position");
	print_vec3(cam.pos, 15);
	ft_printf("%*c %-10s : \n", 10, ' ', "forward");
	print_vec3(cam.fw, 15);
	ft_printf("%*c %-10s : \n", 10, ' ', "right");
	print_vec3(cam.right, 15);
	ft_printf("%*c %-10s : \n", 10, ' ', "up");
	print_vec3(cam.up, 15);
	ft_printf("%*c %-10s : %-10f\n", 10, ' ', "fov", cam.fov);
	ft_printf("%*c %-10s : %-10f\n", 10, ' ', "focal", cam.focal_length);
	ft_printf("%*c %-10s : %-10f\n", 10, ' ', "aperture", cam.aperture);
	ft_printf("%*c %-10s : %-10f\n", 10, ' ', "picasso", cam.picasso);
	ft_printf("%*c %-10s : %-10f\n", 10, ' ', "swirl", cam.swirl);
	if (cam.filter == 0)
		ft_printf("%*c %-10s : %-10s\n", 10, ' ', "filter", "No filter");
	else if (cam.filter == 1)
		ft_printf("%*c %-10s : %-10s\n", 10, ' ', "filter", "Sepia");
	else if (cam.filter == 2)
		ft_printf("%*c %-10s : %-10s\n", 10, ' ', "filter", "Black and white");
	else
		ft_printf("%*c %-10s : %-10s\n", 10, ' ', "filter", "Didnt recognize"
			"filter");
}

void		print_scene_lights(t_scene scene)
{
	int		i;

	i = 0;
	while (i < scene.light_count)
	{
		ft_printf("------------------------------\n");
		ft_printf("%*c %-10s %-10d\n", 5, ' ', "light", i + 1);
		ft_printf("------------------------------\n");
		ft_printf("%*c %-10s :\n", 10, ' ', "position");
		print_vec3(scene.lights[i].pos, 15);
		ft_printf("%*c %-10s :\n", 10, ' ', "color");
		print_color(scene.lights[i].color, 15);
		i++;
	}
}

void		print_scenes(t_scenes *scenes)
{
	int			i;
	int			y;
	int			cam_count;

	i = -1;
	y = -1;
	ft_printf("%*c %-10s : %10d\n", 0, ' ',
		"Number of scenes : ", scenes->scene_count);
	while (++i < scenes->scene_count)
	{
		ft_printf("===== SCENE NUMBER %2d ====\n", i + 1);
		ft_printf("%*c %-10s : %10s\n", 5, ' ', "name", scenes->scene_name[i]);
		ft_printf("%*c %-10s :\n", 5, ' ', "sun direction");
		print_vec3(scenes->scene[i].sun_dir, 10);
		print_vec3(scenes->scene[i].ambient_light_color, 10);
		ft_printf("%*c %-10s :\n", 5, ' ', "ambient light color");
		print_objects(scenes->scene[i]);
		print_scene_lights(scenes->scene[i]);
		cam_count = scenes->cam_count[i];
		while (++y < cam_count)
			print_cam(scenes->cam[i][y], y + 1);
		y = -1;
	}
}
