/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 18:22:41 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/10 18:23:11 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

static void		free_child(t_elem *child, t_elem *bro)
{
	while (child)
	{
		bro = child->next;
		free_elem(child);
		child = bro;
	}
}

void			free_only_one_elem(t_elem *elem)
{
	t_elem	*bro;

	bro = NULL;
	if (elem->type == STRING)
		free(elem->value.stringy);
	if (elem->key)
		free(elem->key);
	free(elem);
}

void			free_elem(t_elem *elem)
{
	t_elem	*bro;
	t_elem	*child;

	bro = NULL;
	if (elem->type == STRING)
		free(elem->value.stringy);
	if (elem->type == OBJECT)
	{
		child = (t_elem *)elem->value.objecty;
		free_child(child, bro);
	}
	if (elem->type == ARRAY)
	{
		child = (t_elem *)elem->value.arrayi;
		free_child(child, bro);
	}
	if (elem->key)
		free(elem->key);
	free(elem);
}
