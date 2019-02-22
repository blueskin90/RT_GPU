/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_forms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:09:16 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 07:49:46 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_objs		*parse_cube(t_json json, t_temp_scene *s,
				t_objs **parent, t_objs **tree)
{
	t_cube			cube;
	t_objs			*obj;
	t_objs			*form;

	parse_common((t_default *)&cube, json.elem, json.config, CUBE);
	cube.size = parse_vec3(json.elem, json.config, "size");
	cube.child_id = -1;
	cube.negative = 0;
	s->cubes[s->cube_count] = cube;
	s->cube_count = s->cube_count + 1;
	add_id(1);
	form = new_objs((void *)&s->cubes[s->cube_count - 1], CUBE, NULL);
	obj = new_objs((void *)&s->cubes[s->cube_count - 1], CUBE, NULL);
	feed_the_trees(tree, form, s->cube_count);
	feed_the_trees(parent, obj, s->cube_count);
	complete_object(obj, (t_json){.config = json.config, .elem = json.elem},
		NUMBER_OBJECT + (s->cube_count - 1));
	complete_object(form, (t_json){.config = json.config, .elem = json.elem},
		NUMBER_OBJECT + (s->cube_count - 1));
	parse_child(s, json, parent, tree);
	return (obj);
}

t_objs		*parse_torus(t_json json, t_temp_scene *s,
				t_objs **parent, t_objs **tree)
{
	t_torus		torus;
	t_objs		*form;
	t_objs		*obj;

	parse_common((t_default *)&torus, json.elem, json.config, TORUS);
	parse_default_material(&torus.material, json.config);
	torus.minor_radius = json_float(json.elem, json.config, "minor_radius");
	torus.major_radius = json_float(json.elem, json.config, "major_radius");
	if (torus.minor_radius > torus.major_radius)
		ft_error("In torus minor radius cannot be bigger than major radius\n");
	s->torus[s->torus_count] = torus;
	s->torus_count = s->torus_count + 1;
	add_id(1);
	form = new_objs((void *)&s->torus[s->torus_count - 1], TORUS, NULL);
	obj = new_objs((void *)&s->torus[s->torus_count - 1], TORUS, NULL);
	feed_the_trees(tree, form, s->torus_count);
	feed_the_trees(parent, obj, s->torus_count);
	complete_object(obj, json, (NUMBER_OBJECT * 2) + s->torus_count);
	complete_object(form, json, (NUMBER_OBJECT * 2) + s->torus_count);
	parse_child(s, json, parent, tree);
	return (obj);
}

t_objs		*parse_capsule(t_json json, t_temp_scene *s,
			t_objs **parent, t_objs **tree)
{
	t_capsule	capsule;
	t_objs		*form;
	t_objs		*obj;

	parse_common((t_default *)&capsule, json.elem, json.config, CAPSULE);
	capsule.radius = json_float(json.elem, json.config, "radius");
	capsule.z = json_float(json.elem, json.config, "z");
	if (s->capsule_count >= NUMBER_OBJECT)
		ft_error("To much capsule\n");
	s->capsules[s->capsule_count] = capsule;
	s->capsule_count = s->capsule_count + 1;
	add_id(1);
	form = new_objs((void *)&s->capsules[s->capsule_count - 1], CAPSULE, NULL);
	obj = new_objs((void *)&s->capsules[s->capsule_count - 1], CAPSULE, NULL);
	feed_the_trees(tree, form, s->capsule_count);
	feed_the_trees(parent, obj, s->capsule_count);
	complete_object(obj, json, (NUMBER_OBJECT * 3) + s->capsule_count);
	complete_object(form, json, (NUMBER_OBJECT * 3) + s->capsule_count);
	parse_child(s, json, parent, tree);
	return (obj);
}
