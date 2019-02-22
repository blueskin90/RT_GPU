/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_child_parent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:53:07 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/17 20:14:49 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cut_and_negative(t_objs *obj, t_objs *parent,
				int bool_neg, t_objs **tree)
{
	t_objs				*temp_objs;
	int					child_id;

	child_id = get_child_id_from_objs(parent);
	if ((child_id != -1 && bool_neg == 2) ||
		(bool_neg == 2 && get_negative_from_objs(parent)))
		ft_error("One negative per object\n");
	temp_objs = parent;
	while (child_id != -1)
	{
		temp_objs = get_obj_by_natural_id((*tree), child_id);
		if (!ft_strcmp(temp_objs->combine, "negative"))
			ft_error("Only one negative per object !\n");
		child_id = get_child_id_from_objs(temp_objs);
	}
	if (temp_objs->type == CUBE)
		((t_cube*)temp_objs->obj)->child_id = obj->natural_id;
	else
		((t_temp_quadric*)temp_objs->obj)->child_id = obj->natural_id;
	if (obj->type == CUBE)
		((t_cube*)obj->obj)->negative = bool_neg;
	else
		((t_temp_quadric*)obj->obj)->negative = bool_neg;
}

void			combine_child_and_parent(t_objs *parent, t_objs *obj,
				t_objs **tree)
{
	int				absolute;
	int				bool_neg;

	parent = get_obj_by_id(parent, obj->id);
	absolute = obj->absolute;
	parent = parent->before;
	bool_neg = 0;
	if (!ft_strcmp("cut", obj->combine) || !ft_strcmp("negative", obj->combine))
	{
		if (!ft_strcmp("cut", obj->combine))
			bool_neg = 1;
		else if (!ft_strcmp("negative", obj->combine))
			bool_neg = 2;
		errors_in_cutting(parent, obj);
		cut_and_negative(obj, parent, bool_neg, tree);
	}
	while (parent && !absolute)
	{
		if (!obj->absolute)
			transform_child_with_parent(obj, parent);
		absolute = parent->absolute;
		parent = parent->before;
	}
}
