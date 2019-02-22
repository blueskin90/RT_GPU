/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaulaus <apaulaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:08:51 by apaulaus          #+#    #+#             */
/*   Updated: 2019/02/12 12:10:52 by apaulaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SCENE_H
# define RT_SCENE_H
# include "rt_object.h"

typedef enum	e_filter
{
	NO_FILTER,
	SEPIA,
	BLACK_AND_WHITE,
}				t_filter;

typedef enum	e_obj_type
{
	SPHERE,
	PLANE,
	CUBE,
	TORUS,
	CAPSULE,
	CYLINDER,
	CONE,
	QUADRIC,
	COPY,
	LIGHT
}				t_obj_type;

typedef enum	e_texture_type
{
	NO_TEXTURE,
	PLAIN_TEXTURE,
	TRANSPARENCE_TEXTURE,
	NORMAL_MAP,
	CHECKERBOARD,
	RIPPLE_EFFECT,
	SPIRAL,
	PERLIN
}				t_texture_type;

typedef struct	s_uniform_buffer_object
{
	float		time;
	uint32_t	frame;
}				t_uniform_buffer_object;

typedef struct	s_cam
{
	t_vec3		pos;
	t_vec3		fw;
	t_vec3		right;
	t_vec3		up;
	uint32_t	filter;
	float		fov;
	float		focal_length;
	float		aperture;
	int			picasso;
	int			swirl;
	float		pad;
	float		pad2;
}				t_cam;

typedef struct	s_scene
{
	t_quadric	quadrics[NUMBER_OBJECT];
	t_cube		cubes[NUMBER_OBJECT];
	t_torus		torus[NUMBER_OBJECT];
	t_capsule	capsules[NUMBER_OBJECT];
	t_light		lights[NUMBER_OBJECT];
	int			quadric_count;
	int			cube_count;
	int			torus_count;
	int			capsule_count;
	int			light_count;
	int			mobius;
	int			motion_blur;
	int			pad2;
	t_vec3		sun_dir;
	t_vec3		ambient_light_color;
}				t_scene;

typedef struct	s_scenes
{
	t_scene		scene[NUMBER_SCENES];
	t_cam		cam[NUMBER_SCENES][NUMBER_CAMERAS];
	char		*scene_name[NUMBER_SCENES];
	int			scene_count;
	int			cam_count[NUMBER_SCENES];
}				t_scenes;

t_scene			get_scene(char *filename);

#endif
