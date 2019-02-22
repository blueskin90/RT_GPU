/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 01:33:42 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 04:52:33 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			get_bool(t_elem *elem)
{
	return (elem->value.booly);
}

static int	json_default_bool(t_elem *config)
{
	t_elem *child_config;

	child_config = get_conf_key_in_parent(config, "default");
	if (child_config->type != BOOL)
		wrong_config_type(child_config->type, BOOL, "default");
	return (get_bool(child_config));
}

int			json_parse_bool(t_elem *elem, t_elem *config)
{
	int			value;

	if (elem == NULL || elem->type == NULL_ELEM)
		return (json_default_bool(config));
	value = get_bool(elem);
	json_min_max_int(value, config);
	return (value);
}

int			json_bool(t_elem *elem, t_elem *config, char *key)
{
	t_elem	*child_config;
	t_elem	*child_elem;

	child_config = get_child_config(key, config);
	child_elem = extract_child(elem, child_config, key, 1);
	return (json_parse_bool(child_elem, child_config));
}
