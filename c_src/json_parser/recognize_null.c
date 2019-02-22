/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_null.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:56:22 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 18:49:24 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

int		json_recognize_null(t_elem *current, char *line, int *i)
{
	if (ft_strncmp(&line[*i], "null", 4) == 0)
	{
		*i = *i + 4;
		current->type = NULL_ELEM;
		current->value.nully = 0;
		return (1);
	}
	return (0);
}
