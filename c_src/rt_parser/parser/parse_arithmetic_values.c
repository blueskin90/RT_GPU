/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arithmetic_values.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:18:34 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/10 20:03:55 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		parse_degree_to_rad(float angle)
{
	if (angle == INFINITY)
		return (INFINITY);
	angle = fmod(angle, 360);
	if (angle < 0)
		angle = angle + 360;
	return (degtorad(angle));
}
