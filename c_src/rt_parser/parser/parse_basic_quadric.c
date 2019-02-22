/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_basic_quadric.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:59:37 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/17 22:37:17 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		prepare_quadric_matrices(t_temp_quadric *quadric)
{
	quadric->rot_mat = parse_rotation_matrix(quadric->transform.rot);
	quadric->trans_mat = parse_translation_matrix(quadric->transform.pos);
	quadric->transformation_matrix =
				matrix_mult(quadric->rot_mat, quadric->trans_mat);
	quadric->child_id = -1;
	quadric->negative = 0;
}

t_objs		*parse_plane(t_json json, t_temp_scene *s,
				t_objs **parent, t_objs **tree)
{
	t_temp_quadric	quadric;
	t_objs			*form;
	t_objs			*obj;

	parse_common((t_default *)&quadric, json.elem, json.config, json.type);
	quadric.matrix = init_full_matrix(
		vec4_init0(0.0, 0.0, 0.0, 0.0),
		vec4_init0(0.0, 0.0, 0.0, 1.0),
		vec4_init0(0.0, 0.0, 0.0, 0.0),
		vec4_init0(0.0, 1.0, 0.0, 0.0));
	prepare_quadric_matrices(&quadric);
	add_id(1);
	form = new_objs((void *)&s->quadrics[s->quadric_count], json.type, NULL);
	obj = new_objs((void *)&s->quadrics[s->quadric_count], json.type, NULL);
	feed_the_trees(tree, form, s->quadric_count);
	feed_the_trees(parent, obj, s->quadric_count);
	complete_object(obj, json, s->quadric_count);
	complete_object(form, json, s->quadric_count);
	s->quadrics[s->quadric_count] = quadric;
	s->quadric_count = s->quadric_count + 1;
	parse_child(s, json, parent, tree);
	return (obj);
}

t_objs		*parse_cylinder(t_json json, t_temp_scene *s,
					t_objs **parent, t_objs **tree)
{
	t_temp_quadric	quadric;
	t_objs			*form;
	t_objs			*obj;
	float			radius;

	radius = json_float(json.elem, json.config, "radius");
	parse_common((t_default *)&quadric, json.elem, json.config, json.type);
	quadric.matrix = init_full_matrix(
		vec4_init0(1.0, 0.0, 0.0, 0.0),
		vec4_init0(0.0, 0.0, 0.0, 0.0),
		vec4_init0(0.0, 0.0, 1.0, 0.0),
		vec4_init0(0.0, 0.0, 0.0, -(radius * radius)));
	prepare_quadric_matrices(&quadric);
	add_id(1);
	form = new_objs((void *)&s->quadrics[s->quadric_count], json.type, NULL);
	obj = new_objs((void *)&s->quadrics[s->quadric_count], json.type, NULL);
	feed_the_trees(tree, form, s->quadric_count);
	feed_the_trees(parent, obj, s->quadric_count);
	complete_object(obj, json, s->quadric_count);
	complete_object(form, json, s->quadric_count);
	s->quadrics[s->quadric_count] = quadric;
	s->quadric_count = s->quadric_count + 1;
	parse_child(s, json, parent, tree);
	return (obj);
}

t_objs		*parse_cone(t_json json, t_temp_scene *s,
			t_objs **parent, t_objs **tree)
{
	t_temp_quadric	quadric;
	t_objs			*form;
	t_objs			*obj;
	float			scale;

	scale = json_float(json.elem, json.config, "scale");
	parse_common((t_default *)&quadric, json.elem, json.config, json.type);
	quadric.matrix = init_full_matrix(
		vec4_init0(1.0 / scale, 0.0, 0.0, 0.0),
		vec4_init0(0.0, -1.0, 0.0, 0.0),
		vec4_init0(0.0, 0.0, 1.0 / scale, 0.0),
		vec4_init0(0.0, 0.0, 0.0, 0.0));
	prepare_quadric_matrices(&quadric);
	add_id(1);
	form = new_objs((void *)&s->quadrics[s->quadric_count], json.type, NULL);
	obj = new_objs((void *)&s->quadrics[s->quadric_count], json.type, NULL);
	feed_the_trees(tree, form, s->quadric_count);
	feed_the_trees(parent, obj, s->quadric_count);
	complete_object(obj, json, s->quadric_count);
	complete_object(form, json, s->quadric_count);
	s->quadrics[s->quadric_count] = quadric;
	s->quadric_count = s->quadric_count + 1;
	parse_child(s, json, parent, tree);
	return (obj);
}

t_objs		*parse_sphere(t_json json, t_temp_scene *s,
			t_objs **parent, t_objs **tree)
{
	t_temp_quadric	quadric;
	t_objs			*form;
	t_objs			*obj;
	float			radius;

	radius = json_float(json.elem, json.config, "radius");
	parse_common((t_default *)&quadric, json.elem, json.config, json.type);
	quadric.matrix = init_full_matrix(
		vec4_init0(1.0, 0.0, 0.0, 0.0),
		vec4_init0(0.0, 1.0, 0.0, 0.0),
		vec4_init0(0.0, 0.0, 1.0, 0.0),
		vec4_init0(0.0, 0.0, 0.0, -(radius * radius)));
	prepare_quadric_matrices(&quadric);
	add_id(1);
	form = new_objs((void *)&s->quadrics[s->quadric_count], json.type, NULL);
	obj = new_objs((void *)&s->quadrics[s->quadric_count], json.type, NULL);
	feed_the_trees(tree, form, s->quadric_count);
	feed_the_trees(parent, obj, s->quadric_count);
	complete_object(obj, json, s->quadric_count);
	complete_object(form, json, s->quadric_count);
	s->quadrics[s->quadric_count] = quadric;
	s->quadric_count = s->quadric_count + 1;
	parse_child(s, json, parent, tree);
	return (obj);
}
