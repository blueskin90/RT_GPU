/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 17:25:42 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/17 22:32:08 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_matrix		parse_rotation_matrix(t_vec4 rot)
{
	t_matrix	rotation_matrix;

	rotation_matrix = rotz_matrix_init(rot.z);
	rotation_matrix = matrix_mult(roty_matrix_init(rot.y), rotation_matrix);
	rotation_matrix = matrix_mult(rotx_matrix_init(rot.x), rotation_matrix);
	return (rotation_matrix);
}

t_matrix		parse_translation_matrix(t_vec3 pos)
{
	return (translation_matrix_init3(vec3_opposite(pos)));
}

t_transform		parse_transform(t_elem *elem, t_elem *config, t_obj_type type)
{
	t_transform		transform;
	t_vec3			rotation;

	transform.pos = parse_vec3(elem, config, "position");
	if (type == CUBE || type == TORUS || type == CAPSULE)
	{
		rotation = parse_vec3_to_rad(elem, config, "rotation");
		transform.rot = qeuler(rotation);
	}
	else
	{
		rotation = parse_vec3(elem, config, "rotation");
		transform.rot = vec4_init0(rotation.x, rotation.y, rotation.z, 0.0);
	}
	return (transform);
}
