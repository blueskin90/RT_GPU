/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hex_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 22:04:43 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/10 20:02:22 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			parse_hex(char *key)
{
	int		value;
	char	*str;
	int		len;

	if (key == NULL)
		return (-1);
	str = ft_string_tolower(key);
	len = ft_strlen(str);
	value = -1;
	if (len > 0 && str[0] == '#')
	{
		str = &str[1];
		value = ft_atoi_base(str, 16);
	}
	else if (len > 1 && str[0] == '0' && str[1] == 'x')
	{
		str = &str[2];
		value = ft_atoi_base(str, 16);
	}
	else if (len > 0 && (ft_isdigit(str[0]) ||
			(str[0] >= 'a' && str[0] <= 'f')))
		value = ft_atoi_base(str, 16);
	else
		ft_error(BAD_FORMAT_HEX);
	return (value);
}
