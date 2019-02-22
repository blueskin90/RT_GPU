/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 17:23:06 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 06:47:03 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_objs			*parse_light(t_json json, t_temp_scene *scene,
				t_objs **parent, t_objs **tree)
{
	t_light			light;
	t_objs			*form;
	t_objs			*obj;
	float			intensity;

	light.color = parse_color(json.elem, json.config, "color");
	intensity = json_float(json.elem, json.config, "light_intensity");
	light.color.x = light.color.x * intensity;
	light.color.y = light.color.y * intensity;
	light.color.z = light.color.z * intensity;
	light.pos = parse_vec3(json.elem, json.config, "position");
	form = new_objs((void *)&scene->lights[scene->light_count],
		json.type, NULL);
	obj = new_objs((void *)&scene->lights[scene->light_count], json.type, NULL);
	add_obj_to_chain(tree, form);
	add_obj_to_chain(parent, obj);
	complete_object(obj, (t_json){.config = json.config, .elem = json.elem},
		(4 * NUMBER_OBJECT) + scene->light_count);
	complete_object(form, (t_json){.config = json.config, .elem = json.elem},
		(4 * NUMBER_OBJECT) + scene->light_count);
	scene->lights[scene->light_count] = light;
	scene->light_count = scene->light_count + 1;
	return (obj);
}
