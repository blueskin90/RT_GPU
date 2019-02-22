/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:51:44 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/10 21:28:46 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_rgb		init_color(float r, float g, float b, int value)
{
	return ((t_rgb){.r = r, .g = g, .b = b, .value = value});
}

static t_rgb		color_from_rgb(t_rgb color, t_rgb def_rgb)
{
	color = default_rgb(color, def_rgb);
	rgb_updatevalue(&color);
	return (color);
}

t_rgb				get_default_rgb(t_elem *elem, t_elem *config)
{
	t_rgb		c;
	char		*key;

	c.r = json_float(elem, config, "r");
	c.g = json_float(elem, config, "g");
	c.b = json_float(elem, config, "b");
	key = json_string_value_or_null(elem, config, "hex");
	c.value = parse_hex(key);
	return (c);
}

t_rgb				extract_rgb(t_elem *elem, t_elem *config)
{
	t_rgb		c;
	char		*key;

	c.r = json_float_value_or_infinity(elem, config, "r");
	c.g = json_float_value_or_infinity(elem, config, "g");
	c.b = json_float_value_or_infinity(elem, config, "b");
	key = json_string_value_or_null(elem, config, "hex");
	c.value = parse_hex(key);
	return (c);
}

t_vec3				parse_color(t_elem *elem, t_elem *config, char *key)
{
	t_rgb		c;
	t_rgb		def_rgb;
	t_elem		*child_config;
	t_elem		*child_elem;

	child_config = get_child_config(key, config);
	child_elem = extract_child(elem, child_config, key, 1);
	c = extract_rgb(child_elem, child_config);
	def_rgb = get_default_rgb(child_elem, child_config);
	if (ft_min(c.r, c.g, c.b) != INFINITY && c.value != -1)
		c = color_from_rgb_and_value(c, def_rgb);
	else if (c.value != -1)
		c = color_from_value(c.value);
	else if (ft_min(c.r, c.g, c.b) != INFINITY)
		c = color_from_rgb(c, def_rgb);
	else
		c = def_rgb;
	c = init_color(c.r / 255.0, c.g / 255.0, c.b / 255.0, c.value);
	return (vec3_init0(c.r, c.g, c.b));
}
