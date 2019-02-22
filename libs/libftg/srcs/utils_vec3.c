/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:15:35 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/28 17:21:16 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

float		min_of_vec3(t_vec3 vec)
{
	if (vec.x <= vec.y && vec.x <= vec.z)
		return (vec.x);
	else if (vec.y <= vec.x && vec.y <= vec.z)
		return (vec.y);
	return (vec.z);
}

float		max_of_vec3(t_vec3 vec)
{
	if (vec.x >= vec.y && vec.x >= vec.z)
		return (vec.x);
	else if (vec.y >= vec.x && vec.y >= vec.z)
		return (vec.y);
	return (vec.z);
}

int			vec3_is_0(t_vec3 vec)
{
	if (fabs(vec.x) == 0.0 && fabs(vec.y) == 0.0 && fabs(vec.z) == 0.0)
		return (1);
	return (0);
}
