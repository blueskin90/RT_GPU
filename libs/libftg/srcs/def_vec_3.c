/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 04:17:32 by toliver           #+#    #+#             */
/*   Updated: 2019/02/01 18:15:51 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_vec3		vec3_init(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = b.x - a.x;
	c.y = b.y - a.y;
	c.z = b.z - a.z;
	c.w = 0;
	return (c);
}

t_vec3		vec3_init0(float x, float y, float z)
{
	t_vec3	c;

	c.x = x;
	c.y = y;
	c.z = z;
	c.w = 0;
	return (c);
}

t_vec3		vec3_x(void)
{
	return (vec3_init0(1, 0, 0));
}

t_vec3		vec3_y(void)
{
	return (vec3_init0(0, 1, 0));
}

t_vec3		vec3_z(void)
{
	return (vec3_init0(0, 0, 1));
}
