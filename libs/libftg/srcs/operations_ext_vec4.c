/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 06:15:34 by toliver           #+#    #+#             */
/*   Updated: 2019/01/28 17:17:19 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

float		vec4_cos(t_vec4 a, t_vec4 b)
{
	return (vec4_dotproduct(a, b) / (vec4_magnitude(a)
				* vec4_magnitude(b)));
}

float		vec4_dot(t_vec4 a, t_vec4 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float		vec4_dotproduct(t_vec4 a, t_vec4 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec4		vec4_div(t_vec4 a, float s)
{
	t_vec4	b;

	if (s == 0.0)
		return (a);
	b.x = a.x / s;
	b.y = a.y / s;
	b.z = a.z / s;
	b.w = 0;
	return (b);
}

t_vec4		vec4_crossproduct(t_vec4 a, t_vec4 b)
{
	t_vec4 c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	c.w = 0;
	return (c);
}
