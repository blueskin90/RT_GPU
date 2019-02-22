/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:41:19 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/29 21:50:20 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				is_equal_vec3(t_vec3 a, t_vec3 b)
{
	if (is_equal_float(a.x, b.x) && is_equal_float(a.y, b.y)
			&& is_equal_float(a.z, b.z))
		return (1);
	return (0);
}

int				is_opposite_vec3(t_vec3 a, t_vec3 b)
{
	return (is_equal_vec3(a, vec3_opposite(b)));
}

int				is_equal_float(float a, float b)
{
	float			c;

	c = a - b;
	c = (c < 0) ? -c : c;
	if (c < TOLERANCE)
		return (1);
	return (0);
}
