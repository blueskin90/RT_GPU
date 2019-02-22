/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaulaus <apaulaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:29:11 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 06:57:01 by apaulaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJECT_H
# define RT_OBJECT_H

# include "rt_math.h"

typedef struct	s_texture
{
	t_vec3		*pixel;
}				t_texture;

typedef struct	s_transform
{
	t_vec3		pos;
	t_vec4		rot;
}				t_transform;

typedef struct	s_material
{
	t_vec3		color;
	float		reflectance;
	float		refraction_index;
	float		opacity;
	float		roughness;
	int			texture_id;
	int			mode;
	float		shift;
	float		stretch;
}				t_material;

typedef struct	s_cube
{
	t_transform	transform;
	t_material	material;
	t_vec3		size;
	int			child_id;
	int			negative;
	int			pad3;
	int			pad4;
}				t_cube;

typedef struct	s_torus
{
	t_transform	transform;
	t_material	material;
	float		major_radius;
	float		minor_radius;
	float		pad1;
	float		pad2;
}				t_torus;

typedef struct	s_capsule
{
	t_transform	transform;
	t_material	material;
	float		radius;
	float		z;
	float		pad1;
	float		pad2;
}				t_capsule;

typedef struct	s_default
{
	t_transform	transform;
	t_material	material;
	int			child_id;
	int			negative;
	int			pad3;
	int			pad4;
}				t_default;

typedef struct	s_quadric
{
	t_material	material;
	t_matrix	matrix;
	int			child_id;
	int			negative;
	int			pad3;
	int			pad4;
}				t_quadric;

typedef struct	s_temp_quadric
{
	t_transform	transform;
	t_material	material;
	int			child_id;
	int			negative;
	t_matrix	transformation_matrix;
	t_matrix	rot_mat;
	t_matrix	trans_mat;
	t_matrix	matrix;
	t_vec3		rot;
	t_vec3		pos;

}				t_temp_quadric;

typedef struct	s_light
{
	t_vec3		color;
	t_vec3		pos;
}				t_light;

#endif
