/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 05:19:28 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 08:01:28 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				is_quadric(t_obj_type type)
{
	if (type == SPHERE || type == PLANE || type == CYLINDER || type == QUADRIC
		|| type == CONE)
		return (1);
	return (0);
}

int				is_basic_quadric(t_obj_type type)
{
	if (type == SPHERE || type == PLANE || type == CYLINDER || type == CONE)
		return (1);
	return (0);
}

int				is_subtractable(t_obj_type type)
{
	if (type == SPHERE || type == PLANE || type == CYLINDER || type == CUBE
	|| type == CONE)
		return (1);
	return (0);
}
