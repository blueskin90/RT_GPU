/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 18:20:37 by toliver           #+#    #+#             */
/*   Updated: 2019/02/10 21:30:19 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rgb			color_from_value(int value)
{
	t_rgb	color;

	color.r = value >> 16;
	color.g = (value >> 8) & 0xFF;
	color.b = (value) & 0xFF;
	color.value = value;
	return (color);
}

t_rgb			color_from_rgb_and_value(t_rgb color, t_rgb def_rgb)
{
	t_rgb	new;

	new = default_rgb(color, def_rgb);
	if (new.value != rgb_getvalue(new))
		ft_error(RGB_HEX_CONFLICT);
	return (new);
}

static int		clampi(int toclamp, int inf, int sup)
{
	if (toclamp < inf)
		return (inf);
	if (toclamp > sup)
		return (sup);
	return (toclamp);
}

void			rgb_updatevalue(t_rgb *rgb)
{
	int			r;
	int			g;
	int			b;

	r = clampi((int)roundf(rgb->r * 255), 0, 255);
	g = clampi((int)roundf(rgb->g * 255), 0, 255);
	b = clampi((int)roundf(rgb->b * 255), 0, 255);
	rgb->value = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int				rgb_getvalue(t_rgb rgb)
{
	int			r;
	int			g;
	int			b;
	int			value;

	r = clampi((int)roundf(rgb.r * 255), 0, 255);
	g = clampi((int)roundf(rgb.g * 255), 0, 255);
	b = clampi((int)roundf(rgb.b * 255), 0, 255);
	value = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (value);
}
