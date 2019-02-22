/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 14:23:43 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 05:03:44 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_elem			*extract_child(t_elem *elem, t_elem *config,
		char *key, int check)
{
	t_elem		*child;

	child = NULL;
	if (elem != NULL)
	{
		if (elem->type == ARRAY)
			child = get_array_elem(elem);
		else if (elem->type == OBJECT)
		{
			child = get_object_elem(elem);
			if (key != NULL)
				child = get_elem_by_key(child, key);
		}
		else
			child = NULL;
	}
	else if (elem == NULL && !is_req(config))
		return (NULL);
	else
		missing_in_json(config->key, NULL);
	if (check)
		check_req_type(child, config);
	return (child);
}

t_elem			*get_conf_key_in_parent(t_elem *elem, char *key)
{
	t_elem		*child;

	child = NULL;
	if (elem != NULL)
	{
		if (elem->type == ARRAY)
			child = get_array_elem(elem);
		else if (elem->type == OBJECT)
		{
			child = get_object_elem(elem);
			child = get_config_by_key(child, key, elem->key);
		}
		else
			child = NULL;
	}
	else
		missing_in_config(key, "config file");
	if (child == NULL)
		missing_in_config(key, elem->key);
	return (child);
}

t_elem			*extract_config_child(t_elem *elem, char *error_key)
{
	t_elem		*child;

	child = NULL;
	if (elem != NULL)
	{
		if (elem->type == ARRAY)
			child = get_array_elem(elem);
		else if (elem->type == OBJECT)
			child = get_object_elem(elem);
		else
			child = NULL;
	}
	else
		missing_in_config(error_key, "config file");
	if (child == NULL)
		missing_in_config(error_key, elem->key);
	return (child);
}

t_elem			*json_get_key(t_elem *elem, t_elem *config, char *key)
{
	t_elem	*child_config;
	t_elem	*child_elem;

	child_config = get_child_config(key, config);
	child_elem = extract_child(elem, child_config, key, 1);
	return (elem);
}
