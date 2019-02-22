/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_elem_architecture.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 00:36:25 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 18:48:41 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

static void		show_json_data(t_elem *elem, int padding)
{
	if (elem->type == INTEGER)
		ft_printf("%*ctype : %s\n", padding, ' ', "INTEGER");
	if (elem->type == FLOAT)
		ft_printf("%*ctype : %s\n", padding, ' ', "FLOAT");
	if (elem->type == STRING)
		ft_printf("%*ctype : %s\n", padding, ' ', "STRING");
	if (elem->type == BOOL)
		ft_printf("%*ctype : %s\n", padding, ' ', "BOOL");
	if (elem->type == NULL_ELEM)
		ft_printf("%*ctype : %s\n", padding, ' ', "NULL");
	if (elem->type == ARRAY)
		ft_printf("%*ctype : %s\n", padding, ' ', "ARRAY");
	if (elem->type == OBJECT)
		ft_printf("%*ctype : %s\n", padding, ' ', "OBJECT");
}

void			show_elem(t_elem *elem)
{
	if (elem)
	{
		ft_printf("%c--------\n", '-');
		ft_printf("key : %s\n", elem->key);
		ft_printf("closed : %d\n", elem->closed);
		ft_printf("type : %d\n", elem->type);
		show_json_data(elem, 0);
		if (elem->type == INTEGER)
			ft_printf("value : %d\n", elem->value.inty);
		if (elem->type == FLOAT)
			ft_printf("value : %f\n", elem->value.floaty);
		if (elem->type == STRING)
			ft_printf("value : %s\n", elem->value.stringy);
		if (elem->type == BOOL)
			ft_printf("value : %d\n", elem->value.booly);
		if (elem->type == NULL_ELEM)
			ft_printf("value : %d\n", elem->value.nully);
		ft_printf("%c--------\n", '-');
	}
}

static void		show_value(t_elem *elem, int padding)
{
	t_elem	*bro;

	if (elem->type == INTEGER)
		ft_printf("%*cvalue : %d\n", padding, ' ', elem->value.inty);
	if (elem->type == FLOAT)
		ft_printf("%*cvalue : %f\n", padding, ' ', elem->value.floaty);
	if (elem->type == STRING)
		ft_printf("%*cvalue : %s\n", padding, ' ', elem->value.stringy);
	if (elem->type == BOOL)
		ft_printf("%*cvalue : %d\n", padding, ' ', elem->value.booly);
	if (elem->type == NULL_ELEM)
		ft_printf("%*cvalue : %d\n", padding, ' ', elem->value.nully);
	if (elem->type == ARRAY)
	{
		bro = (t_elem *)elem->value.arrayi;
		while (bro)
		{
			show_one_elem(bro, padding + 10);
			bro = bro->next;
		}
	}
}

void			show_one_elem(t_elem *elem, int padding)
{
	t_elem	*bro;

	ft_printf("%*c--------\n", padding, '-');
	ft_printf("%*ckey : %s\n", padding, ' ', elem->key);
	ft_printf("%*cclosed : %d\n", padding, ' ', elem->closed);
	show_json_data(elem, padding);
	show_value(elem, padding);
	ft_printf("%*c--------\n", padding, '-');
	if (elem->type == OBJECT)
	{
		bro = (t_elem *)elem->value.objecty;
		while (bro)
		{
			show_one_elem(bro, padding + 10);
			bro = bro->next;
		}
	}
}

void			show_every_elem(t_elem *elem, int padding)
{
	t_elem *current;

	current = elem;
	while (current)
	{
		show_one_elem(current, padding);
		current = current->next;
	}
}
