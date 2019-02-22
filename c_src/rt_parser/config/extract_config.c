/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 18:46:19 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/10 19:10:52 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_elem		*get_childs_of_config(t_elem *parent)
{
	t_elem *childrens;

	childrens = extract_config_child(parent, NULL);
	childrens = get_config_by_key(childrens, "childs", parent->key);
	childrens = extract_config_child(childrens, "child");
	return (childrens);
}

t_elem		*get_child_config(char *key, t_elem *parent_config)
{
	t_elem *config;

	if (parent_config == NULL)
		missing_in_config(key, NULL);
	config = get_childs_of_config(parent_config);
	config = get_config_by_key(config, key, parent_config->key);
	return (config);
}

t_elem		*get_config_by_key(t_elem *elem, char *key, char *parent)
{
	t_elem *curr;

	curr = elem;
	while (curr)
	{
		if (curr->key != NULL && !ft_strcmp(curr->key, key))
			return (curr);
		curr = curr->next;
	}
	missing_in_config(key, parent);
	return (NULL);
}
