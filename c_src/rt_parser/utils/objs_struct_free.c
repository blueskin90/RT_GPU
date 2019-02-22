/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_struct_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 04:02:06 by toliver           #+#    #+#             */
/*   Updated: 2019/02/11 05:07:56 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj_type		free_in_parent_tree_from_child(t_objs **tree, t_objs *obj)
{
	t_objs		*curr;
	t_objs		*temp;
	t_obj_type	type;

	curr = (*tree);
	type = SPHERE;
	while (curr)
	{
		if (curr->next != NULL && (curr->next->id == obj->id))
		{
			temp = curr->next;
			free_objs(temp);
			type = curr->type;
			curr->next = NULL;
			return (type);
		}
		curr = curr->next;
	}
	ft_error("ID of child could not be found in the tree\n"
		"free_in_parent_from_child() in objs_struct.c");
	return (1);
}

void			free_objs_parent(t_objs *tree)
{
	t_objs		*tmp;

	while (tree)
	{
		tmp = tree->next;
		free(tree);
		if (tmp && tmp->parent_tree)
			free_objs(tmp->parent_tree);
		tree = tmp;
	}
}

void			free_objs(t_objs *tree)
{
	t_objs		*tmp;

	while (tree)
	{
		tmp = tree->next;
		free(tree);
		tree = tmp;
	}
}
