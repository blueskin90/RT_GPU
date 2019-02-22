/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 22:53:30 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 20:31:34 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

/*
** This function tries to recognize if the given element is formatted to be an
** ARRAY
** RETURN 1 if array is recognized
** RETURN 0 if array is NOT recognized
*/

int			json_recognize_string(t_elem *current, char *line, int *i)
{
	int		len;
	char	*str;
	int		begin;

	len = 0;
	if (line[*i] != '"')
		return (0);
	*i = *i + 1;
	begin = *i;
	while (line[*i] != '\0' && line[*i] != '"')
	{
		if (len == INT_MAX)
			json_error(STRING_TO_LONG);
		len++;
		*i = *i + 1;
	}
	if (line[*i] != '"')
		json_error(JSON_PARSING_ERROR);
	*i = *i + 1;
	if ((str = ft_strsub(line, begin, (size_t)len)) == NULL)
		json_error(MALLOC_FAIL);
	current->type = STRING;
	current->value.stringy = str;
	return (1);
}
