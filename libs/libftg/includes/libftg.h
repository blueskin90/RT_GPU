/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftg.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:54:24 by toliver           #+#    #+#             */
/*   Updated: 2019/02/11 09:59:06 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTG_H
# define LIBFTG_H

# include <math.h>

typedef struct		s_vec3
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec3;

typedef struct		s_vec4
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec4;

typedef struct		s_matrix
{
	float			matrix[4][4];
}					t_matrix;

typedef struct		s_mat4
{
	t_vec4			a;
	t_vec4			b;
	t_vec4			c;
	t_vec4			d;
}					t_mat4;
/*
** Generic functions
*/
float				ft_min(float a, float b, float c);
float				ft_max(float a, float b, float c);
/*
** Vector and Vertex matrix and math handling functions
*/
t_vec4				vec4_x(void);
t_vec4				vec4_y(void);
t_vec4				vec4_z(void);
t_vec4				vec4_init0(float x, float y, float z, float w);
t_vec3				vec3_x(void);
t_vec3				vec3_y(void);
t_vec3				vec3_z(void);
t_vec3				vec3_init(t_vec3 a, t_vec3 b);
t_vec3				vec3_init0(float x, float y, float z);
t_vec3				vec3_add(t_vec3 a, t_vec3 b);
t_vec3				vec3_sub(t_vec3 a, t_vec3 b);
t_vec3				vec3_mul(t_vec3 a, float s);
t_vec3				vec3_opposite(t_vec3 a);
float				vec3_cos(t_vec3 a, t_vec3 b);
float				vec3_dot(t_vec3 a, t_vec3 b);
float				vec3_dotproduct(t_vec3 a, t_vec3 b);
t_vec3				vec3_div(t_vec3 a, float s);
t_vec3				vec3_crossproduct(t_vec3 a, t_vec3 b);
float				vec4_cos(t_vec4 a, t_vec4 b);
float				vec4_dot(t_vec4 a, t_vec4 b);
float				vec4_dotproduct(t_vec4 a, t_vec4 b);
t_vec4				vec4_div(t_vec4 a, float s);
t_vec4				vec4_crossproduct(t_vec4 a, t_vec4 b);
t_vec4				vec4_add(t_vec4 a, t_vec4 b);
t_vec4				vec4_sub(t_vec4 a, t_vec4 b);
t_vec4				vec4_mul(t_vec4 a, float s);
t_vec4				vec4_opposite(t_vec4 a);
float				min_of_vec3(t_vec3 vec);
float				max_of_vec3(t_vec3 vec);
int					vec3_is_0(t_vec3 vec);
float				min_of_vec4(t_vec4 vec);
float				max_of_vec4(t_vec4 vec);
int					vec4_is_0(t_vec4 vec);
t_vec3				vec3_normalize(t_vec3 a);
t_vec3				vec3_norm(t_vec3 a);
float				vec3_magnitude(t_vec3 a);
t_vec4				vec4_normalize(t_vec4 a);
t_vec4				vec4_norm(t_vec4 a);
float				vec4_magnitude(t_vec4 a);
float				degtorad(float deg);
float				radtodeg(float rad);

t_vec4				qeuler(t_vec3 euler);
t_vec3				quat_to_euler(t_vec4 quat);
/*
**	MATRIX
*/
t_matrix			matrix_mult(t_matrix a, t_matrix b);
t_vec3				matrix_mult_vec3(t_matrix a, t_vec3 b);
t_vec4				matrix_mult_vec4(t_matrix a, t_vec4 b);
t_matrix			matrix_transpose(t_matrix matrix);
t_matrix			identity_matrix_init(void);
t_matrix			scale_matrix_init(float scale);
t_matrix			translation_matrix_init3(t_vec3 tranvec);
t_matrix			translation_matrix_init4(t_vec4 tranvec);
t_matrix			rotmatrix_axis_angle(t_vec3 axis, float angle);
t_matrix			rotx_matrix_init(float degrees);
t_matrix			roty_matrix_init(float degrees);
t_matrix			rotz_matrix_init(float degrees);
t_matrix			init_full_matrix(t_vec4 a, t_vec4 b, t_vec4 c, t_vec4 d);
t_mat4				identity_mat4_init(void);
#endif
