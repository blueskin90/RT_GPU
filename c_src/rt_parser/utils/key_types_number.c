/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_types_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 21:05:58 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 06:36:00 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			check_float_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(key, "ambiant") || !compare(key, "radius")
	|| !compare(key, "roll") || !compare(key, "fov")
		|| !compare(key, "focal_length") || !compare(key, "aperture")
		|| !compare(key, "r") || !compare(key, "g") || !compare(key, "b")
		|| !compare(key, "x") || !compare(key, "y") || !compare(key, "z")
		|| !compare(key, "z") || !compare(key, "a") || !compare(key, "b")
		|| !compare(key, "c") || !compare(key, "d") || !compare(key, "e")
		|| !compare(key, "f") || !compare(key, "g") || !compare(key, "h")
		|| !compare(key, "i") || !compare(key, "j")
		|| !compare(key, "reflectance") || !compare(key, "refraction_index")
		|| !compare(key, "opacity") || !compare(key, "roughness")
		|| !compare(key, "half_angle") || !compare(key, "size")
		|| !compare(key, "major_radius") || !compare(key, "minor_radius")
		|| !compare(key, "angle"))
		return (1);
	wrong_format(key, FLOAT);
	return (0);
}

int			check_bool_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(key, "light"))
		return (1);
	wrong_format(key, BOOL);
	return (0);
}

int			check_int_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(key, "r") || !compare(key, "g") || !compare(key, "fov")
			|| !compare(key, "light") || !compare(key, "radius")
			|| !compare(key, "focal_length") || !compare(key, "aperture")
			|| !compare(key, "x") || !compare(key, "y") || !compare(key, "z")
			|| !compare(key, "a") || !compare(key, "b") || !compare(key, "c")
			|| !compare(key, "d") || !compare(key, "e") || !compare(key, "f")
			|| !compare(key, "g") || !compare(key, "h") || !compare(key, "i")
			|| !compare(key, "j") || !compare(key, "reflectance")
			|| !compare(key, "refraction_index") || !compare(key, "opacity")
			|| !compare(key, "roughness") || !compare(key, "roll")
			|| !compare(key, "angle") || !compare(key, "half_angle")
			|| !compare(key, "size") || !compare(key, "major_radius")
			|| !compare(key, "minor_radius") || !compare(key, "b"))
		return (1);
	wrong_format(key, INTEGER);
	return (0);
}
