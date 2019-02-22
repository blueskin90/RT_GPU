/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 09:54:24 by toliver           #+#    #+#             */
/*   Updated: 2019/02/11 09:54:26 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

float		vec4_magnitude(t_vec4 a)
{
	return (sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2)));
}

t_vec4		vec4_norm(t_vec4 a)
{
	float	magnitude;
	t_vec4	b;

	magnitude = vec4_magnitude(a);
	if (magnitude == 0.0)
		return (a);
	b.x = a.x / magnitude;
	b.y = a.y / magnitude;
	b.z = a.z / magnitude;
	b.w = 0;
	return (b);
}

t_vec4		vec4_normalize(t_vec4 a)
{
	float	magnitude;
	t_vec4	b;

	magnitude = vec4_magnitude(a);
	if (magnitude == 0.0)
		return (a);
	b.x = a.x / magnitude;
	b.y = a.y / magnitude;
	b.z = a.z / magnitude;
	b.w = 0;
	return (b);
}
