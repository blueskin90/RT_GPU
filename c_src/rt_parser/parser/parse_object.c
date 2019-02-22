/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 18:47:21 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 04:34:29 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_obj_func g_obj_f[] =
{
	{SPHERE, &parse_sphere},
	{PLANE, &parse_plane},
	{CUBE, &parse_cube},
	{TORUS, &parse_torus},
	{CAPSULE, &parse_capsule},
	{CYLINDER, &parse_cylinder},
	{CONE, &parse_cone},
	{QUADRIC, &parse_quadric},
	{COPY, &parse_copy},
	{LIGHT, &parse_light},
	{0, NULL}
};

static int			get_obj_type_name(char *str)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(str, "sphere"))
		return (SPHERE);
	else if (!compare(str, "plane"))
		return (PLANE);
	else if (!compare(str, "cube"))
		return (CUBE);
	else if (!compare(str, "torus"))
		return (TORUS);
	else if (!compare(str, "capsule"))
		return (CAPSULE);
	else if (!compare(str, "cylinder"))
		return (CYLINDER);
	else if (!compare(str, "cone"))
		return (CONE);
	else if (!compare(str, "quadric"))
		return (QUADRIC);
	else if (!compare(str, "copy"))
		return (COPY);
	else if (!compare(str, "light"))
		return (LIGHT);
	return (QUADRIC);
}

t_objs				*parse_object(t_json json,
		t_temp_scene *scene, t_objs **parent, t_objs **tree)
{
	t_elem		*child_elem;
	t_elem		*child_config;
	t_objs		*obj;
	char		*str;
	int			i;

	child_config = get_child_config("type", json.config);
	child_elem = extract_child(json.elem, child_config, "type", 1);
	str = json_parse_string(child_elem, child_config);
	json.type = get_obj_type_name(str);
	i = 0;
	while (g_obj_f[i].f != NULL)
	{
		if (g_obj_f[i].type == json.type)
			obj = g_obj_f[i].f(json, scene, parent, tree);
		i++;
	}
	return (obj);
}
