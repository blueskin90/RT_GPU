/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:00:31 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 18:04:20 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

/*
** This function tries to recognize if the given element is formatted to be an
** NUMBER
** 1 IS INT, 2 IS FLOAT, 0 IS NOT A NUMBER
** RETURN 1 if NUMBER is recognized
** RETURN 0 if NUMBER is NOT recognized
*/

static int		valid_number(char *line, int i, int *len)
{
	char	coma;
	int		begin;
	int		i_tmp;

	i_tmp = i;
	coma = 0;
	begin = i_tmp;
	if (line[i_tmp] == '-' || line[i_tmp] == '+')
		i_tmp = i_tmp + 1;
	while (ft_isdigit(line[i_tmp]) && line[i_tmp] != '\0')
		i_tmp = i_tmp + 1;
	if (line[i_tmp] == '.')
	{
		coma = 1;
		i_tmp = i_tmp + 1;
		while (ft_isdigit(line[i_tmp]) && line[i_tmp] != '\0')
			i_tmp = i_tmp + 1;
	}
	*len = i_tmp - begin;
	if (!(end_of_value(line[i_tmp])))
		return (0);
	else if (coma)
		return (2);
	else
		return (1);
}

static void		init_int_elem(t_elem *current, int x, int *i, int len)
{
	current->value.inty = x;
	current->type = INTEGER;
	*i = *i + len;
}

static void		init_float_elem(t_elem *current, float dec, int *i, int len)
{
	current->value.floaty = dec;
	current->type = FLOAT;
	*i = *i + len;
}

int				json_recognize_number(t_elem *current, char *line, int *i)
{
	int				len;
	char			type;
	char			*tmp;

	len = 0;
	if (!(type = valid_number(line, *i, &len)) || len == 0)
		return (0);
	if ((tmp = ft_strsub(line, *i, (size_t)len)) == NULL)
		json_error(MALLOC_FAIL);
	if (type == 1)
	{
		init_int_elem(current, ft_atoi(tmp), i, len);
		free(tmp);
		return (current->type);
	}
	if (type == 2)
	{
		init_float_elem(current, ft_atof(tmp), i, len);
		free(tmp);
		return (current->type);
	}
	return (0);
}
