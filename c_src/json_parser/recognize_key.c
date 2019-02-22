/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:34:19 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 20:34:30 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

static char		*create_key(char *line, int begin, int len, int *i)
{
	char	*ptr;

	*i = *i + 1;
	if ((ptr = ft_strsub(line, begin, (size_t)len)) == NULL)
		json_error(MALLOC_FAIL);
	return (ptr);
}

int				recognize_key(int *i, t_elem *current, char *line, int fd)
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
	if (line[*i] != '"' || len == 0)
		json_error(JSON_PARSING_ERROR);
	*i = *i + 1;
	ignore_tab_and_spaces(&line, i, fd, 0);
	if (line[*i] != ':')
		json_error(JSON_PARSING_ERROR);
	str = create_key(line, begin, len, i);
	current->key = str;
	return (1);
}
