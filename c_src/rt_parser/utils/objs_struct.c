/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 03:47:10 by toliver           #+#    #+#             */
/*   Updated: 2019/02/11 04:27:17 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_objs			*new_objs(void *obj, t_obj_type type, char *name)
{
	t_objs		*new;

	new = ft_malloc(sizeof(t_objs));
	new->obj = obj;
	new->type = type;
	new->name = name;
	new->absolute = 0;
	new->combine = NULL;
	new->next = NULL;
	new->before = NULL;
	new->id = get_obj_id();
	return (new);
}

void			add_obj_to_chain(t_objs **main, t_objs *new)
{
	t_objs		*curr;

	if (main == NULL || (*main) == NULL)
	{
		(*main) = new;
	}
	else
	{
		curr = (*main);
		while (curr->next)
		{
			curr = curr->next;
		}
		curr->next = new;
		new->before = curr;
	}
}

int				number_of_objs_with_name(t_objs **tree, char *key)
{
	t_objs		*curr;
	int			nbr;

	nbr = 0;
	curr = (*tree);
	while (curr)
	{
		if (curr->name != NULL && !ft_strcmp(curr->name, key))
			nbr++;
		curr = curr->next;
	}
	return (nbr);
}

t_objs			*copy_tree(t_objs **tree)
{
	t_objs		*curr;
	t_objs		*begin;
	t_objs		*tmp;

	begin = NULL;
	curr = (*tree);
	while (curr)
	{
		tmp = ft_memcpy(ft_malloc(sizeof(t_objs)), curr, sizeof(t_objs));
		tmp->next = NULL;
		tmp->before = NULL;
		add_obj_to_chain(&begin, tmp);
		curr = curr->next;
	}
	return (begin);
}
