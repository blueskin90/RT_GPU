/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:48:50 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 07:21:09 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_temp_scene		init_temp_scene(void)
{
	t_temp_scene		scene;

	scene.cube_count = 0;
	scene.torus_count = 0;
	scene.capsule_count = 0;
	scene.quadric_count = 0;
	scene.light_count = 0;
	return (scene);
}

void					parse_sun(t_temp_scene *scene,
						t_elem *elem, t_elem *config)
{
	scene->sun_dir = parse_vec3(elem, config, "sun_direction");
	if (!(scene->sun_dir.x < 0.01 && scene->sun_dir.y < 0.01
		&& scene->sun_dir.z < 0.01))
		scene->sun_dir = vec3_normalize(scene->sun_dir);
	scene->ambient_light_color = parse_color(elem, config,
		"ambient_color");
}

static int				parse_all_objects(t_json objects, t_temp_scene *scene,
			t_objs **parent, t_objs **tree)
{
	t_objs			*obj;
	t_json			object;
	int				nbr_object;

	nbr_object = 0;
	object.config = get_child_config("object", objects.config);
	object.elem = extract_child(objects.elem, object.config, NULL, 1);
	while (object.elem && nbr_object < NUMBER_OBJECTS)
	{
		obj = parse_object((t_json){.config = object.config,
			.elem = object.elem}, scene, parent, tree);
		free_objs(*parent);
		(*parent) = NULL;
		object.elem = object.elem->next;
		nbr_object++;
	}
	return (nbr_object);
}

t_temp_scene			parse_scene(t_elem *elem, t_elem *config)
{
	t_temp_scene	scene;
	t_json			objects;
	t_objs			*parent;
	t_objs			*tree;
	int				nbr_object;

	parent = NULL;
	tree = NULL;
	set_id(0);
	scene = init_temp_scene();
	objects.config = get_child_config("objects", config);
	objects.elem = extract_child(elem, objects.config, "objects", 1);
	nbr_object = 0;
	if (objects.elem)
		nbr_object = parse_all_objects(objects, &scene, &parent, &tree);
	parse_sun(&scene, elem, config);
	calculate_all_matrices(&tree);
	free_objs(parent);
	free_objs_parent(tree);
	check_nbr_elements(nbr_object, objects.config);
	return (scene);
}
