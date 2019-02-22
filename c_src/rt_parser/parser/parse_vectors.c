/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:10:28 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 04:36:08 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3		parse_vec3_to_rad(t_elem *elem, t_elem *config, char *key)
{
	t_elem	*child_config;
	t_elem	*child_elem;

	child_config = get_child_config(key, config);
	child_elem = extract_child(elem, child_config, key, 1);
	return (vec3_init0(parse_degree_to_rad(
		json_float(child_elem, child_config, "x")),
		parse_degree_to_rad(
		json_float(child_elem, child_config, "y")),
		parse_degree_to_rad(
		json_float(child_elem, child_config, "z"))));
}

t_vec3		parse_vec3(t_elem *elem, t_elem *config, char *key)
{
	t_elem	*child_config;
	t_elem	*child_elem;
	t_vec3	vec;

	child_config = get_child_config(key, config);
	child_elem = extract_child(elem, child_config, key, 1);
	vec = vec3_init0(
		json_float(child_elem, child_config, "x"),
		json_float(child_elem, child_config, "y"),
		json_float(child_elem, child_config, "z"));
	return (vec);
}
