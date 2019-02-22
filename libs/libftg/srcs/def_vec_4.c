/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 04:17:32 by toliver           #+#    #+#             */
/*   Updated: 2019/01/28 17:02:33 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_vec4		vec4_init0(float x, float y, float z, float w)
{
	t_vec4	c;

	c.x = x;
	c.y = y;
	c.z = z;
	c.w = w;
	return (c);
}

t_vec4		vec4_x(void)
{
	return (vec4_init0(1, 0, 0, 1));
}

t_vec4		vec4_y(void)
{
	return (vec4_init0(0, 1, 0, 1));
}

t_vec4		vec4_z(void)
{
	return (vec4_init0(0, 0, 1, 1));
}
