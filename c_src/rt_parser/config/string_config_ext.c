/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_config_ext.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 19:54:15 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/10 19:59:08 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		json_accepted_entries(t_elem *elem, t_elem *config)
{
	t_elem	*child_config;
	t_elem	*accepted;
	t_elem	*begin;

	child_config = get_conf_key_in_parent(config, "accepted_entries");
	if (child_config->type == STRING
		&& !ft_strcmp(get_string(child_config), "*"))
		return ;
	else if (child_config->type != ARRAY)
		wrong_config_type(child_config->type, ARRAY, "accepted_entries");
	accepted = get_conf_key_in_parent(child_config, NULL);
	begin = accepted;
	while (accepted)
	{
		if (!ft_strcmp(get_string(accepted), get_string(elem)))
			return ;
		accepted = accepted->next;
	}
	error_accepted_entries(get_string(elem), begin, elem->key);
}
