/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 17:10:44 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 05:04:25 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float		json_get_min_float(t_elem *config)
{
	t_elem			*child_config;
	float			min;

	min = 0;
	child_config = get_conf_key_in_parent(config, "min");
	if (child_config->type == STRING
			&& !ft_strcmp(get_string(child_config), "INFINITY"))
		min = INFINITY;
	else if (child_config->type == STRING
			&& !ft_strcmp(get_string(child_config), "-INFINITY"))
		min = -INFINITY;
	else if (child_config->type != FLOAT)
		wrong_config_type(child_config->type, FLOAT, "min");
	else
		min = get_float(child_config);
	return (min);
}

static float		json_get_max_float(t_elem *config)
{
	t_elem			*child_config;
	float			max;

	max = 0;
	child_config = get_conf_key_in_parent(config, "max");
	if (child_config->type == STRING
			&& !ft_strcmp(get_string(child_config), "INFINITY"))
		max = INFINITY;
	else if (child_config->type == STRING
			&& !ft_strcmp(get_string(child_config), "-INFINITY"))
		max = -INFINITY;
	else if (child_config->type != FLOAT)
		wrong_config_type(child_config->type, FLOAT, "max");
	else
		max = get_float(child_config);
	return (max);
}

void				json_min_max_float(float value, t_elem *config)
{
	float			min;
	float			max;
	int				min_included;
	int				max_included;
	t_elem			*child_config;

	min = json_get_min_float(config);
	max = json_get_max_float(config);
	child_config = get_conf_key_in_parent(config, "min_included");
	if (child_config->type != BOOL)
		wrong_config_type(child_config->type, FLOAT, "min_included");
	min_included = get_integer(child_config);
	child_config = get_conf_key_in_parent(config, "max_included");
	if (child_config->type != BOOL)
		wrong_config_type(child_config->type, FLOAT, "max_included");
	max_included = get_integer(child_config);
	if (float_is_smaller(min_included, min, value) ||
			float_is_bigger(max_included, max, value))
		bad_limits_float(min, max, value, config->key);
}

void				json_min_max_int(int value, t_elem *config)
{
	int			min;
	int			max;
	int			min_included;
	int			max_included;
	t_elem		*child_config;

	child_config = get_conf_key_in_parent(config, "min");
	if (child_config->type != INTEGER)
		wrong_config_type(child_config->type, INTEGER, "min");
	min = get_integer(child_config);
	child_config = get_conf_key_in_parent(config, "max");
	if (child_config->type != INTEGER)
		wrong_config_type(child_config->type, INTEGER, "max");
	max = get_integer(child_config);
	child_config = get_conf_key_in_parent(config, "min_included");
	if (child_config->type != BOOL)
		wrong_config_type(child_config->type, FLOAT, "min_included");
	min_included = get_integer(child_config);
	child_config = get_conf_key_in_parent(config, "max_included");
	if (child_config->type != BOOL)
		wrong_config_type(child_config->type, FLOAT, "max_included");
	max_included = get_integer(child_config);
	if (int_is_smaller(min_included, min, value) ||
			int_is_bigger(max_included, max, value))
		bad_limits_int(min, max, value, config->key);
}
