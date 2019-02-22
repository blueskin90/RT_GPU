/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 02:36:37 by toliver           #+#    #+#             */
/*   Updated: 2019/02/11 07:15:17 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				get_negative_from_objs(t_objs *obj)
{
	t_temp_quadric	*quadric;
	t_cube			*cube;

	if (obj->type == CUBE)
	{
		cube = (t_cube*)obj->obj;
		return (cube->negative);
	}
	else if (is_basic_quadric(obj->type))
	{
		quadric = (t_temp_quadric*)obj->obj;
		return (quadric->negative);
	}
	else
	{
		ft_dprintf(1, "How did you manage to bring ");
		print_obj_type(obj->type);
		ft_dprintf(1, "to this subtract function. This object does not"
					"subtract\n");
		exit(0);
	}
	return (0);
}

int				get_child_id_from_objs(t_objs *obj)
{
	t_temp_quadric	*quadric;
	t_cube			*cube;

	if (obj->type == CUBE)
	{
		cube = (t_cube*)obj->obj;
		return (cube->child_id);
	}
	else if (is_basic_quadric(obj->type))
	{
		quadric = (t_temp_quadric*)obj->obj;
		return (quadric->child_id);
	}
	else
	{
		ft_dprintf(1, "How did you manage to bring ");
		print_obj_type(obj->type);
		ft_dprintf(1, "to this subtract function. This object does not "
						"subtract\n");
		exit(0);
	}
	return (0);
}

void			errors_in_cutting(t_objs *parent, t_objs *obj)
{
	if (parent->combine != NULL && (!ft_strcmp("cut", parent->combine)
			|| !ft_strcmp("negative", parent->combine)))
		ft_error("No n-th cut or negative\n");
	if (!is_basic_quadric(obj->type) || !is_subtractable(parent->type))
		ft_error("negative child can only be basic forms : \
				SPHERE CYLINDER PLANE CONE\n");
}

void			calculate_all_matrices(t_objs **tree)
{
	t_objs		*curr;

	curr = (*tree);
	while (curr)
	{
		if (curr->parent_tree)
			combine_child_and_parent(curr->parent_tree, curr, tree);
		curr = curr->next;
	}
}
