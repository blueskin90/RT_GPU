/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:48:15 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 02:55:37 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				float_is_smaller(int included, float small, float x)
{
	if (!included)
	{
		if (x <= small)
			return (1);
	}
	else
	{
		if (x < small)
			return (1);
	}
	return (0);
}

int				float_is_bigger(int included, float big, float x)
{
	if (!included)
	{
		if (x >= big)
			return (1);
	}
	else
	{
		if (x > big)
			return (1);
	}
	return (0);
}

int				int_is_smaller(int included, int small, int x)
{
	if (!included)
	{
		if (x <= small)
			return (1);
	}
	else
	{
		if (x < small)
			return (1);
	}
	return (0);
}

int				int_is_bigger(int included, int big, int x)
{
	if (!included)
	{
		if (x >= big)
			return (1);
	}
	else
	{
		if (x > big)
			return (1);
	}
	return (0);
}
