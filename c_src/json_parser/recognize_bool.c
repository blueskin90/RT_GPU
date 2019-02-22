/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_bool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:34:41 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 18:57:14 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

int		json_recognize_bool(t_elem *current, char *line, int *i)
{
	if (ft_strncmp(&line[*i], "true", 4) == 0)
	{
		*i = *i + 4;
		current->type = BOOL;
		current->value.booly = TRUE;
		return (1);
	}
	else if (ft_strncmp(&line[*i], "false", 5) == 0)
	{
		*i = *i + 5;
		current->type = BOOL;
		current->value.booly = FALSE;
		return (1);
	}
	return (0);
}
