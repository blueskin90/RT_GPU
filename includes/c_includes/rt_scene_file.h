/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene_file.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaulaus <apaulaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:08:51 by apaulaus          #+#    #+#             */
/*   Updated: 2019/02/12 12:11:09 by apaulaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SCENE_FILE_H
# define RT_SCENE_FILE_H

# include "rt.h"
# include "rt_scene.h"
# include "rt_object.h"

typedef struct		s_temp_scene
{
	t_temp_quadric	quadrics[NUMBER_OBJECT];
	t_cube			cubes[NUMBER_OBJECT];
	t_torus			torus[NUMBER_OBJECT];
	t_capsule		capsules[NUMBER_OBJECT];
	t_light			lights[NUMBER_OBJECT];
	int				quadric_count;
	int				cube_count;
	int				torus_count;
	int				capsule_count;
	int				light_count;
	t_vec3			sun_dir;
	t_vec3			ambient_light_color;
}					t_temp_scene;

typedef struct		s_temp_scenes
{
	t_temp_scene	scene[NUMBER_SCENES];
	t_cam			cam[NUMBER_SCENES][NUMBER_CAMERAS];
	char			*scene_name[NUMBER_SCENES];
	int				scene_count;
	int				cam_count[NUMBER_SCENES];
}					t_temp_scenes;

#endif
