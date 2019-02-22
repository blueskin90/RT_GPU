/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 20:51:49 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/10 20:20:08 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		complete_child_object(t_json json, t_objs *obj,
				t_objs **parent, t_objs **tree)
{
	t_objs		*tree_obj;

	obj->combine =
		json_string(json.elem, json.config, "combine");
	obj->absolute =
		json_bool(json.elem, json.config, "absolute");
	tree_obj = get_obj_by_id(*tree, obj->id);
	tree_obj->parent_tree = copy_tree(parent);
	free_in_parent_tree_from_child(parent, obj);
}

void			parse_child(t_temp_scene *scene, t_json json,
				t_objs **parent, t_objs **tree)
{
	t_json		child_json;
	t_json		object_json;
	t_objs		*obj;

	child_json.config =
		get_child_config("children", json.config);
	child_json.elem =
		extract_child(json.elem, child_json.config, "children", 1);
	if (json.elem)
	{
		object_json.config =
			get_child_config("child", child_json.config);
		object_json.elem =
			extract_child(child_json.elem, object_json.config, NULL, 1);
		while (object_json.elem)
		{
			obj = parse_object(
				(t_json){.elem = object_json.elem, .config = json.config},
						scene, parent, tree);
			complete_child_object(
				(t_json){.elem = object_json.elem, .config =
				object_json.config}, obj, parent, tree);
			object_json.elem = object_json.elem->next;
		}
	}
}
