/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_init_rot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:55:11 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 09:58:43 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_mat4		mat4_axis_angle_get(t_vec3 axis, float cos, float sin,
				float t)
{
	t_mat4	mat4;
	float	tmp1;
	float	tmp2;

	mat4 = identity_mat4_init();
	mat4.a.x = cos + axis.x * axis.x * t;
	mat4.b.y = cos + axis.y * axis.y * t;
	mat4.c.z = cos + axis.z * axis.z * t;
	tmp1 = axis.x * axis.y * t;
	tmp2 = axis.z * sin;
	mat4.b.x = tmp1 + tmp2;
	mat4.a.y = tmp1 - tmp2;
	tmp1 = axis.x * axis.z * t;
	tmp2 = axis.y * sin;
	mat4.c.x = tmp1 - tmp2;
	mat4.a.z = tmp1 + tmp2;
	tmp1 = axis.y * axis.z * t;
	tmp2 = axis.x * sin;
	mat4.c.y = tmp1 + tmp2;
	mat4.b.z = tmp1 - tmp2;
	return (mat4);
}
