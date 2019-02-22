/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_child_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:04:06 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 08:00:46 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			both_are_quadrics(t_objs *child, t_objs *parent)
{
	t_temp_quadric		*quadric_parent;
	t_temp_quadric		*quadric_child;

	quadric_child = (t_temp_quadric*)child->obj;
	quadric_parent = (t_temp_quadric*)parent->obj;
	quadric_child->transformation_matrix = matrix_mult(
		quadric_child->transformation_matrix, quadric_parent->rot_mat);
	quadric_child->transformation_matrix = matrix_mult(
		quadric_child->transformation_matrix, quadric_parent->trans_mat);
}

void			child_not_quadric(t_objs *child, t_objs *parent)
{
	t_default			*def_child;
	t_temp_quadric		*quadric_parent;
	t_vec4				rotation;
	t_vec3				position;

	def_child = (t_default*)child->obj;
	quadric_parent = (t_temp_quadric*)parent->obj;
	rotation = qeuler((t_vec3){ .x= quadric_parent->transform.rot.x,
		.y = quadric_parent->transform.rot.y,
		.z = quadric_parent->transform.rot.z});
	position = qmulvec(def_child->transform.pos, qconjugate(rotation));
	def_child->transform.pos = vec3_add(position,
		quadric_parent->transform.pos);
	def_child->transform.rot = qmult(def_child->transform.rot, rotation);
}

void			parent_not_quadric(t_objs *child, t_objs *parent)
{
	t_temp_quadric		*quadric_child;
	t_default			*def_parent;
	t_matrix			translation_matrix;
	t_matrix			rotation_matrix;
	t_vec3				rot;

	quadric_child = (t_temp_quadric*)child->obj;
	def_parent = (t_default*)parent->obj;
	rot = quat_to_euler(def_parent->transform.rot);
	rotation_matrix = parse_rotation_matrix((t_vec4){
		.x = rot.x,
		.y = rot.y,
		.z = rot.z
	});
	translation_matrix = parse_translation_matrix(def_parent->transform.pos);
	quadric_child->transformation_matrix = matrix_mult(
			quadric_child->transformation_matrix, rotation_matrix);
	quadric_child->transformation_matrix = matrix_mult(
			quadric_child->transformation_matrix, translation_matrix);
}

void			transform_child_with_parent(t_objs *child, t_objs *parent)
{
	t_default			*def_parent;
	t_default			*def_child;
	t_vec3				position;

	if (is_quadric(child->type) && is_quadric(parent->type))
		both_are_quadrics(child, parent);
	else if (!is_quadric(child->type) && is_quadric(parent->type))
		child_not_quadric(child, parent);
	else if (is_quadric(child->type) && !is_quadric(parent->type))
		parent_not_quadric(child, parent);
	else if (!is_quadric(child->type) && !is_quadric(parent->type))
	{
		def_child = (t_default*)child->obj;
		def_parent = (t_default*)parent->obj;
		position = qmulvec(def_child->transform.pos,
			qconjugate(def_parent->transform.rot));
		def_child->transform.pos =
				vec3_add(position, def_parent->transform.pos);
		def_child->transform.rot =
				qmult(def_child->transform.rot, def_parent->transform.rot);
	}
}
