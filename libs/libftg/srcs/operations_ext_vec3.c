/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_ext_vec3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:16:13 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 09:12:28 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

float		vec3_cos(t_vec3 a, t_vec3 b)
{
	return (vec3_dotproduct(a, b) / (vec3_magnitude(a)
				* vec3_magnitude(b)));
}

float		vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float		vec3_dotproduct(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3		vec3_div(t_vec3 a, float s)
{
	t_vec3	b;

	if (s == 0.0)
		return (a);
	b.x = a.x / s;
	b.y = a.y / s;
	b.z = a.z / s;
	return (b);
}

t_vec3		vec3_crossproduct(t_vec3 a, t_vec3 b)
{
	t_vec3 c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}
