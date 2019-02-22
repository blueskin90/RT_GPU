/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_types_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 21:05:19 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 08:03:54 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_array_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(key, "parent_element") ||
			!compare(key, "spheres") ||
			!compare(key, "cylinders") ||
			!compare(key, "planes") ||
			!compare(key, "cones") ||
			!compare(key, "objects") ||
			!compare(key, "cameras") ||
			!compare(key, "scenes") ||
			!compare(key, "lights"))
		return (1);
	wrong_format(key, ARRAY);
	return (0);
}

static int		check_object_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(key, "translation") ||
			!compare(key, "scene") ||
			!compare(key, "value") ||
			!compare(key, "size") ||
			!compare(key, "object") ||
			!compare(key, "objects") ||
			!compare(key, "camera") ||
			!compare(key, "forward") ||
			!compare(key, "position") ||
			!compare(key, "rotation") ||
			!compare(key, "color"))
		return (1);
	wrong_format(key, OBJECT);
	return (0);
}

static int		check_string_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(key, "name") ||
			!compare(key, "filter") ||
			!compare(key, "type") ||
			!compare(key, "hex"))
		return (1);
	wrong_format(key, STRING);
	return (0);
}

static int		check_null_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(key, "ambiant") ||
			!compare(key, "radius") ||
			!compare(key, "x") ||
			!compare(key, "y") ||
			!compare(key, "z") ||
			!compare(key, "r") ||
			!compare(key, "g") ||
			!compare(key, "b"))
		return (1);
	wrong_format(key, NULL_ELEM);
	return (0);
}

int				check_type_of_key(char *key, t_json_data type)
{
	if (type == FLOAT)
		return (check_float_keys(key));
	else if (type == OBJECT)
		return (check_object_keys(key));
	else if (type == ARRAY)
		return (check_array_keys(key));
	else if (type == INTEGER)
		return (check_int_keys(key));
	else if (type == NULL_ELEM)
		return (check_null_keys(key));
	else if (type == STRING)
		return (check_string_keys(key));
	else if (type == BOOL)
	{
		return (check_bool_keys(key));
	}
	return (0);
}
