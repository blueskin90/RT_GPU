/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_type_of_key.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:21:48 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 04:10:34 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_json_data		get_type_of_key(char *key)
{
	key = ft_string_tolower(key);
	if (!ft_strcmp(key, "float"))
		return (FLOAT);
	else if (!ft_strcmp(key, "integer") || !ft_strcmp(key, "int"))
		return (INTEGER);
	else if (!ft_strcmp(key, "string"))
		return (STRING);
	else if (!ft_strcmp(key, "bool") || !ft_strcmp(key, "boolean"))
		return (BOOL);
	else if (!ft_strcmp(key, "object"))
		return (OBJECT);
	else if (!ft_strcmp(key, "array"))
		return (ARRAY);
	else if (!ft_strcmp(key, "null"))
		return (NULL_ELEM);
	else
		ft_error("could not recognize type of $key");
	return (NOTYPE);
}

t_elem			*get_elem_by_key(t_elem *elem, char *key)
{
	t_elem		*curr;

	curr = elem;
	while (curr)
	{
		if (curr->key != NULL && !ft_strcmp(curr->key, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
