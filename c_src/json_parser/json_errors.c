/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 21:17:26 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 09:47:23 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

void		json_error(char *error)
{
	int		line_number;

	line_number = get_line_number();
	ft_printf("ERROR on line %d : ", line_number);
	ft_error(error);
}

void		error_free_line(char *line, char *error)
{
	free(line);
	line = NULL;
	json_error(error);
}
