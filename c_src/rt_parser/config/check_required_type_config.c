/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_required_type_config.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 15:22:20 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 04:56:55 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				is_req(t_elem *config)
{
	t_elem		*req;
	t_elem		*childs;
	int			required;

	childs = extract_config_child(config, config->key);
	req = get_config_by_key(childs, "required", config->key);
	if (req->type != BOOL)
		wrong_config_type(req->type, BOOL, req->key);
	required = req->value.booly;
	return (required);
}

int				check_req(t_elem *json, t_elem *config)
{
	int			required;

	required = is_req(config);
	if (json == NULL && required)
		is_required(config->key, 0);
	else if (json == NULL)
		return (0);
	return (1);
}

void			check_type(t_elem *elem, t_elem *config)
{
	t_json_data		config_type;
	t_elem			*child_config;

	child_config = extract_config_child(config, config->key);
	child_config = get_config_by_key(child_config, "type", config->key);
	if (child_config == NULL)
		is_req_in_config("type", config->key);
	if (child_config->type != STRING)
		wrong_config_type(child_config->type, STRING, config->key);
	config_type = get_type_of_key(get_string(child_config));
	if (config_type != elem->type
		&& !(config_type == FLOAT && elem->type == INTEGER))
		wrong_config_type(elem->type, config_type, config->key);
}

void			check_req_type(t_elem *json, t_elem *config)
{
	if (!check_req(json, config))
		return ;
	check_type(json, config);
}
