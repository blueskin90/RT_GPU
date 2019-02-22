/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qeuler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:55:15 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 10:06:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_vec3		quat_to_euler(t_vec4 quat)
{
	t_vec3	euler;

	euler.x = atan2(2 * ((quat.w * quat.x) + (quat.y * quat.z)), 1 - 2
		* (quat.x * quat.x + quat.y * quat.y));
	euler.y = asin(2 * ((quat.w * quat.y) - (quat.z * quat.x)));
	euler.z = atan2(2 * ((quat.w * quat.z) + (quat.x * quat.y)), 1 - 2
		* (quat.y * quat.y + quat.z * quat.z));
	return (euler);
}

void		qeuler_init(float var[6], t_vec3 euler)
{
	var[0] = cos(euler.z * 0.5);
	var[1] = sin(euler.z * 0.5);
	var[2] = cos(euler.y * 0.5);
	var[3] = sin(euler.y * 0.5);
	var[4] = cos(euler.x * 0.5);
	var[5] = sin(euler.x * 0.5);
}

t_vec4		qeuler(t_vec3 euler)
{
	float	var[6];
	t_vec4	q;

	qeuler_init(var, euler);
	q.w = var[0] * var[2] * var[4] + var[1] * var[3] * var[5];
	q.x = var[0] * var[2] * var[5] - var[1] * var[3] * var[4];
	q.y = var[1] * var[2] * var[5] + var[0] * var[3] * var[4];
	q.z = var[1] * var[2] * var[4] - var[0] * var[3] * var[5];
	return (q);
}
