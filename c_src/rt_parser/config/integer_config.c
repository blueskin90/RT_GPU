/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 17:00:06 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 05:13:42 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				get_integer(t_elem *elem)
{
	return (elem->value.inty);
}

static int		json_default_int(t_elem *config)
{
	t_elem	*child_config;

	child_config = get_conf_key_in_parent(config, "default");
	if (child_config->type != INTEGER)
		wrong_config_type(child_config->type, INTEGER, "default");
	return (get_integer(child_config));
}

int				json_parse_int(t_elem *elem, t_elem *config)
{
	int		value;

	if (elem == NULL || elem->type == NULL_ELEM)
		return (json_default_int(config));
	value = get_integer(elem);
	json_min_max_int(value, config);
	return (value);
}

int				json_integer(t_elem *elem, t_elem *config, char *key)
{
	t_elem	*child_config;
	t_elem	*child_elem;

	child_config = get_child_config(key, config);
	child_elem = extract_child(elem, child_config, key, 1);
	return (json_parse_int(child_elem, child_config));
}
