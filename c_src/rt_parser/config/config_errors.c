/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 18:57:20 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/10 19:58:36 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			wrong_config_type(t_json_data actual, t_json_data should,
		char *key)
{
	if (key)
		ft_dprintf(2, "The type of %s should not be ", key);
	else
		ft_dprintf(2, "the type of (?) should not be ");
	print_data_type(actual);
	ft_dprintf(2, " but should be ");
	print_data_type(should);
	ft_dprintf(2, "\n");
	exit(0);
}

void			missing_in_config(char *key, char *parent)
{
	if (parent && key)
		ft_dprintf(2, "CONFIG FILE : the key %s is missing in %s\n",
			key, parent);
	else if (key)
		ft_dprintf(2, "CONFIG FILE : the key %s is missing\n", key);
	exit(0);
}

void			error_accepted_entries(char *value, t_elem *config, char *key)
{
	ft_printf("'%s' of %s key is not included in the accepted entries :  \n",
				value, key);
	while (config)
	{
		ft_printf("%s\n", get_string(config));
		config = config->next;
	}
	exit(0);
}
