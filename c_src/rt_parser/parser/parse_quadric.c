/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quadric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 00:06:57 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 06:17:21 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_matrix		parse_quadric_matrix(t_elem *elem, t_elem *config)
{
	t_matrix	mat;
	t_elem		*child_config;
	t_elem		*child_elem;

	child_config = get_child_config("value", config);
	child_elem = extract_child(elem, child_config, "value", 1);
	mat = init_full_matrix(
				vec4_init0(json_float(child_elem, child_config, "a"),
					json_float(child_elem, child_config, "b"),
					json_float(child_elem, child_config, "c"),
					json_float(child_elem, child_config, "d")),
				vec4_init0(json_float(child_elem, child_config, "b"),
					json_float(child_elem, child_config, "e"),
					json_float(child_elem, child_config, "f"),
					json_float(child_elem, child_config, "g")),
				vec4_init0(json_float(child_elem, child_config, "c"),
					json_float(child_elem, child_config, "f"),
					json_float(child_elem, child_config, "h"),
					json_float(child_elem, child_config, "i")),
				vec4_init0(json_float(child_elem, child_config, "d"),
					json_float(child_elem, child_config, "g"),
					json_float(child_elem, child_config, "i"),
					json_float(child_elem, child_config, "j")));
	return (mat);
}

static void		if_complex_quadric_is_light(int light, t_temp_quadric *quadric,
				t_json json)
{
	float				intensity;

	if (light)
	{
		quadric->material.reflectance = -1;
		intensity = json_float(json.elem, json.config, "light_intensity");
		quadric->material.color.x = quadric->material.color.x * intensity;
		quadric->material.color.y = quadric->material.color.y * intensity;
		quadric->material.color.z = quadric->material.color.z * intensity;
	}
}

static void		rotation_complex_quadric(t_temp_quadric *quadric, t_json json)
{
	quadric->matrix = parse_quadric_matrix(json.elem, json.config);
	quadric->transform.pos = parse_vec3(json.elem, json.config, "position");
	quadric->rot = parse_vec3(json.elem, json.config, "rotation");
	quadric->transform.rot = vec4_init0(quadric->rot.x, quadric->rot.y,
			quadric->rot.z, 0);
	quadric->rot_mat = parse_rotation_matrix(quadric->transform.rot);
	quadric->trans_mat = parse_translation_matrix(quadric->transform.pos);
	quadric->transformation_matrix =
		matrix_mult(quadric->rot_mat, quadric->trans_mat);
}

t_objs			*parse_quadric(t_json json, t_temp_scene *scene,
				t_objs **parent, t_objs **tree)
{
	t_temp_quadric		quadric;
	int					light;
	t_objs				*form;
	t_objs				*obj;

	quadric.material = parse_material(json.elem, json.config);
	light = json_bool(json.elem, json.config, "light");
	if_complex_quadric_is_light(light, &quadric, json);
	rotation_complex_quadric(&quadric, json);
	quadric.child_id = -1;
	quadric.negative = 0;
	scene->quadrics[scene->quadric_count] = quadric;
	scene->quadric_count = scene->quadric_count + 1;
	add_id(1);
	form = new_objs((void *)&scene->quadrics[scene->quadric_count - 1],
				QUADRIC, NULL);
	obj = new_objs((void *)&scene->quadrics[scene->quadric_count - 1],
				QUADRIC, NULL);
	complete_object(obj, json, scene->quadric_count - 1);
	complete_object(form, json, scene->quadric_count - 1);
	add_obj_to_chain(tree, form);
	add_obj_to_chain(parent, obj);
	parse_child(scene, (t_json){.elem = json.elem, .config = json.config},
				parent, tree);
	return (form);
}
