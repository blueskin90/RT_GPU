/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 17:01:55 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/15 20:16:24 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			get_float(t_elem *elem)
{
	return (elem->value.floaty);
}

static float	json_default_float(t_elem *config)
{
	t_elem		*child_config;

	child_config = get_conf_key_in_parent(config, "default");
	if (child_config->type != FLOAT)
		wrong_config_type(child_config->type, FLOAT, "default");
	return (get_float(child_config));
}

float			json_float_value_or_infinity(t_elem *elem, t_elem *config,
				char *key)
{
	t_elem		*child_config;
	t_elem		*child_elem;
	float		value;

	value = 0;
	if (elem == NULL)
		return (INFINITY);
	child_config = get_child_config(key, config);
	child_elem = extract_child(elem, child_config, key, 1);
	if (child_elem == NULL && is_req(child_config))
		is_required(key, 0);
	else if (child_elem == NULL || child_elem->type == NULL_ELEM)
		return (INFINITY);
	else if (child_elem->type == INTEGER)
		value = (float)get_integer(child_elem);
	else
		value = get_float(child_elem);
	json_min_max_float(value, child_config);
	return (value);
}

float			json_parse_float(t_elem *elem, t_elem *config)
{
	float		value;

	if (elem == NULL || elem->type == NULL_ELEM)
		return (json_default_float(config));
	if (elem->type == INTEGER)
		value = (float)get_integer(elem);
	else
		value = get_float(elem);
	json_min_max_float(value, config);
	return (value);
}

float			json_float(t_elem *elem, t_elem *config, char *key)
{
	t_elem	*child_config;
	t_elem	*child_elem;

	child_config = get_child_config(key, config);
	child_elem = extract_child(elem, child_config, key, 1);
	return (json_parse_float(child_elem, child_config));
}
