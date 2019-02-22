/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 04:25:54 by toliver           #+#    #+#             */
/*   Updated: 2019/01/28 17:13:47 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_vec4		vec4_add(t_vec4 a, t_vec4 b)
{
	t_vec4	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = 0;
	return (c);
}

t_vec4		vec4_sub(t_vec4 a, t_vec4 b)
{
	t_vec4	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = 0;
	return (c);
}

t_vec4		vec4_mul(t_vec4 a, float s)
{
	t_vec4	b;

	b.x = a.x * s;
	b.y = a.y * s;
	b.z = a.z * s;
	b.w = 0;
	return (b);
}

t_vec4		vec4_opposite(t_vec4 a)
{
	t_vec4	b;

	b.x = -a.x;
	b.y = -a.y;
	b.z = -a.z;
	b.w = 0;
	return (b);
}
