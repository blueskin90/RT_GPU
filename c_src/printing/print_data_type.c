/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 20:30:53 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/04 23:51:20 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		print_obj_type(t_obj_type type)
{
	if (type == SPHERE)
		ft_printf("SPHERE");
	if (type == QUADRIC)
		ft_printf("QUADRIC");
	if (type == CUBE)
		ft_printf("CUBE");
	if (type == TORUS)
		ft_printf("TORUS");
	if (type == CYLINDER)
		ft_printf("CYLINDER");
	if (type == CONE)
		ft_printf("CONE");
	if (type == PLANE)
		ft_printf("PLANE");
}

void		print_data_type(t_json_data type)
{
	if (type == INTEGER)
		ft_printf("INTEGER");
	if (type == FLOAT)
		ft_printf("FLOAT");
	if (type == STRING)
		ft_printf("STRING");
	if (type == BOOL)
		ft_printf("BOOL");
	if (type == NULL_ELEM)
		ft_printf("NULL");
	if (type == ARRAY)
		ft_printf("ARRAY");
	if (type == OBJECT)
		ft_printf("OBJECT");
}
