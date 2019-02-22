/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_recursive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 02:57:11 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 15:10:11 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

/*
**	When Element found is an array,
**	search trough all child element of this array.
*/

t_elem		*array_recursive(int fd, char **line, int *i)
{
	t_elem	*current;
	char	type_found;

	if (DEBUG_PRINT)
		ft_printf("NEW ARRAY ELEMENT\n");
	type_found = 0;
	current = create_elem();
	ignore_tab_and_spaces(line, i, fd, 0);
	if ((type_found = json_recognize_array(current, line, i, fd)) == 1)
		type_found = current->type;
	else if ((type_found = json_recognize_object(current, line, i, fd)) != 0)
		type_found = current->type;
	else if (!(recognize_type(current, line, i)))
		json_error(VALUE_NOT_RECOGNIZED);
	ignore_tab_and_spaces(line, i, fd, 0);
	return (current);
}
