/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_equals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 17:55:50 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/27 18:02:47 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_string_equals(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (0);
	return (ft_string_compare(s1, s2) == 0);
}
