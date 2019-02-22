/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_struct_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 04:02:14 by toliver           #+#    #+#             */
/*   Updated: 2019/02/11 04:03:14 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_objs			*get_obj_by_natural_id(t_objs *main, int obj_id)
{
	t_objs		*curr;

	curr = main;
	while (curr)
	{
		if (curr->natural_id == obj_id)
			return (curr);
		curr = curr->next;
	}
	ft_error("No object with natural id has been found\n");
	return (NULL);
}

t_objs			*get_obj_by_id(t_objs *main, int obj_id)
{
	t_objs		*curr;

	curr = main;
	while (curr)
	{
		if (curr->id == obj_id)
			return (curr);
		curr = curr->next;
	}
	ft_error("No object with id has been found\n");
	return (NULL);
}

t_objs			*get_obj_by_name(t_objs **tree, char *key)
{
	t_objs		*curr;

	curr = (*tree);
	while (curr)
	{
		if (curr->name != NULL && !ft_strcmp(curr->name, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
