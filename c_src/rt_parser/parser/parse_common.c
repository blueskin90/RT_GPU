/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 00:13:07 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 07:46:16 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	complete_object(t_objs *obj, t_json json, int natural_id)
{
	obj->name = json_string(json.elem, json.config, "name");
	obj->natural_id = natural_id;
	obj->absolute = json_bool(json.elem, json.config, "absolute");
	obj->combine = json_string(json.elem, json.config, "combine");
	obj->json = json;
	obj->parent_tree = NULL;
}

void	parse_common(t_default *def, t_elem *elem,
				t_elem *config, t_obj_type type)
{
	int		light;
	float	intensity;

	def->transform = parse_transform(elem, config, type);
	def->material = parse_material(elem, config);
	light = json_bool(elem, config, "light");
	if (light)
	{
		def->material.reflectance = -1;
		intensity = json_float(elem, config, "light_intensity");
		def->material.color.x = def->material.color.x * intensity;
		def->material.color.y = def->material.color.y * intensity;
		def->material.color.z = def->material.color.z * intensity;
	}
}

void	feed_the_trees(t_objs **tree, t_objs *obj, int count)
{
	if (count + 1 >= 128)
		ft_error("To much of a certain type of object");
	add_obj_to_chain(tree, obj);
}
