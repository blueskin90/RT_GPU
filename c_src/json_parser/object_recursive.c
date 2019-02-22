/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_recursive.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 02:57:42 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 15:29:32 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

t_elem		*json_recursive(int fd, char **line, int *i)
{
	t_elem	*current;
	char	type_found;

	type_found = 0;
	current = create_elem();
	ignore_tab_and_spaces(line, i, fd, 0);
	if ((recognize_key(i, current, *line, fd)) == 0)
		error_free_line(*line, KEY_NOT_FOUND);
	ignore_tab_and_spaces(line, i, fd, 0);
	if ((type_found = json_recognize_array(current, line, i, fd)) != 0)
		type_found = current->type;
	else if ((type_found = json_recognize_object(current, line, i, fd)) != 0)
		type_found = current->type;
	else if (!(recognize_type(current, line, i)))
		json_error(VALUE_NOT_RECOGNIZED);
	ignore_tab_and_spaces(line, i, fd, 0);
	while ((*line)[*i] == ',')
	{
		*i = *i + 1;
		current->next = json_recursive(fd, line, i);
		ignore_tab_and_spaces(line, i, fd, 0);
	}
	return (current);
}
