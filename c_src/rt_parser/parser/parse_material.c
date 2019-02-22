/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 17:27:55 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 08:53:23 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			get_texture_mode(char *str)
{
	int				(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(ft_string_tolower(str), "none"))
		return (NO_TEXTURE);
	else if (!compare(ft_string_tolower(str), "plain texture"))
		return (PLAIN_TEXTURE);
	else if (!compare(ft_string_tolower(str), "transparency"))
		return (TRANSPARENCE_TEXTURE);
	else if (!compare(ft_string_tolower(str), "normal map"))
		return (NORMAL_MAP);
	else if (!compare(ft_string_tolower(str), "checkerboard"))
		return (CHECKERBOARD);
	else if (!compare(ft_string_tolower(str), "ripples"))
		return (RIPPLE_EFFECT);
	else if (!compare(ft_string_tolower(str), "spiral"))
		return (SPIRAL);
	else if (!compare(ft_string_tolower(str), "perlin"))
		return (PERLIN);
	return (NO_TEXTURE);
}

static	int			get_mapping(char *str)
{
	int				(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(ft_string_tolower(str), "spherical"))
		return (0);
	else if (!compare(ft_string_tolower(str), "planar"))
		return (1);
	return (0);
}

void				parse_default_material(t_material *material, t_elem *config)
{
	char			*key;
	int				mapping;

	if (material->reflectance != -1)
		material->reflectance = json_float(NULL, config, "reflectance");
	material->refraction_index = json_float(NULL, config, "refraction_index");
	material->opacity = json_float(NULL, config, "opacity");
	material->roughness = json_float(NULL, config, "roughness");
	material->texture_id = json_integer(NULL, config, "texture");
	key = json_string(NULL, config, "mode");
	material->mode = get_texture_mode(key);
	key = json_string(NULL, config, "mapping");
	mapping = get_mapping(key);
	if (mapping == 0)
		material->mode = material->mode;
	else if (mapping == 1)
		material->mode = -material->mode;
	material->stretch = json_float(NULL, config, "stretch");
	material->shift = json_float(NULL, config, "shift");
}

t_material			parse_material(t_elem *elem, t_elem *config)
{
	t_material		material;
	char			*key;
	int				mapping;

	material.color = parse_color(elem, config, "color");
	material.reflectance = json_float(elem, config, "reflectance");
	material.refraction_index = json_float(elem, config, "refraction_index");
	material.opacity = json_float(elem, config, "opacity");
	material.roughness = json_float(elem, config, "roughness");
	material.texture_id = json_integer(elem, config, "texture");
	key = json_string(elem, config, "mode");
	material.mode = get_texture_mode(key);
	key = json_string(elem, config, "mapping");
	mapping = get_mapping(key);
	if (mapping == 0)
		material.mode = material.mode;
	else if (mapping == 1)
		material.mode = -material.mode;
	material.stretch = json_float(elem, config, "stretch");
	material.shift = json_float(elem, config, "shift");
	return (material);
}
