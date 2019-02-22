/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_up_right_rot.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:37:38 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/28 19:55:37 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			get_right_dir(t_vec3 dir)
{
	if (is_equal_vec3(dir, vec3_y()))
		return (vec3_x());
	else if (is_equal_vec3(dir, vec3_opposite(vec3_y())))
		return (vec3_x());
	return (vec3_normalize(vec3_opposite(vec3_crossproduct(dir, vec3_y()))));
}

t_vec3			get_up_dir(t_vec3 dir, t_vec3 right)
{
	return (vec3_norm(vec3_crossproduct(dir, right)));
}

t_vec3			vec_rot_zaxis_angle(t_vec3 v, t_vec3 zaxis, float angle)
{
	t_matrix	rotmatrix;

	rotmatrix = rotmatrix_axis_angle(zaxis, -angle);
	return (matrix_mult_vec3(rotmatrix, v));
}
