/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 02:00:09 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 19:53:07 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

/*
** This function tries to recognize if the given element is formatted to be an
** OBJECT
** RETURN 1 if object is recognized
** RETURN 0 if object is NOT recognized
*/

static inline void	object_chain_array(t_elem **current,
		t_elem **previous, t_elem *child)
{
	if (!(*current)->value.objecty)
		(*current)->value.arrayi = (void *)child;
	if ((*previous))
		(*previous)->next = child;
	(*previous) = child;
}

int					json_recognize_object(t_elem *current, char **line,
		int *i, int fd)
{
	t_elem	*child;
	t_elem	*previous;
	char	first_elem;

	first_elem = 1;
	previous = NULL;
	if ((*line)[*i] != '{')
		return (0);
	*i = *i + 1;
	current->type = OBJECT;
	ignore_tab_and_spaces(line, i, fd, 0);
	while ((*line)[*i] == ',' || (first_elem && ((*line)[*i] != '}')))
	{
		first_elem = 0;
		if ((*line)[*i] == ',')
			*i = *i + 1;
		ignore_tab_and_spaces(line, i, fd, 0);
		child = json_recursive(fd, line, i);
		ignore_tab_and_spaces(line, i, fd, 0);
		object_chain_array(&current, &previous, child);
	}
	((*line)[*i] != '}') ? json_error(OBJECT_BAD_FORMAT) : 0;
	current->closed = 1;
	*i = *i + 1;
	return (current->type);
}
