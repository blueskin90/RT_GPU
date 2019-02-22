/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 20:23:54 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 05:14:22 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char			*get_string(t_elem *elem)
{
	return (elem->value.stringy);
}

char			*json_string_value_or_null(t_elem *elem,
				t_elem *config, char *key)
{
	t_elem	*child_config;
	t_elem	*child_elem;
	int		size;

	if (elem == NULL)
		return (NULL);
	child_config = get_child_config(key, config);
	child_elem = extract_child(elem, child_config, key, 1);
	if (child_elem == NULL && is_req(child_config))
		is_required(key, 0);
	else if (child_elem == NULL || child_elem->type == NULL_ELEM)
		return (NULL);
	key = get_string(child_elem);
	size = (int)ft_strlen(key);
	json_min_max_int(size, child_config);
	json_accepted_entries(child_elem, child_config);
	return (key);
}

static char		*json_default_string(t_elem *config)
{
	t_elem	*child_config;

	child_config = get_conf_key_in_parent(config, "default");
	if (child_config->type != STRING)
		wrong_config_type(child_config->type, STRING, "default");
	return (get_string(child_config));
}

char			*json_parse_string(t_elem *elem, t_elem *config)
{
	int			size;

	if (elem == NULL || get_string(elem) == NULL)
		return (json_default_string(config));
	size = (int)ft_strlen(get_string(elem));
	json_min_max_int(size, config);
	json_accepted_entries(elem, config);
	return (get_string(elem));
}

char			*json_string(t_elem *elem, t_elem *config, char *key)
{
	t_elem	*child_config;
	t_elem	*child_elem;

	child_config = get_child_config(key, config);
	child_elem = extract_child(elem, child_config, key, 1);
	return (json_parse_string(child_elem, child_config));
}
