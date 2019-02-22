/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 04:25:54 by toliver           #+#    #+#             */
/*   Updated: 2019/01/28 17:13:57 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_vec3		vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vec3		vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_vec3		vec3_mul(t_vec3 a, float s)
{
	t_vec3	b;

	b.x = a.x * s;
	b.y = a.y * s;
	b.z = a.z * s;
	return (b);
}

t_vec3		vec3_opposite(t_vec3 a)
{
	t_vec3	b;

	b.x = -a.x;
	b.y = -a.y;
	b.z = -a.z;
	return (b);
}
