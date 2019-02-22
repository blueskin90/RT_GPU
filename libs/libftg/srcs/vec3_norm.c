/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:13:02 by toliver           #+#    #+#             */
/*   Updated: 2019/02/11 09:53:57 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

float		vec3_magnitude(t_vec3 a)
{
	return (sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2)));
}

t_vec3		vec3_norm(t_vec3 a)
{
	float	magnitude;
	t_vec3	b;

	magnitude = vec3_magnitude(a);
	if (magnitude == 0.0)
		return (a);
	b.x = a.x / magnitude;
	b.y = a.y / magnitude;
	b.z = a.z / magnitude;
	return (b);
}

t_vec3		vec3_normalize(t_vec3 a)
{
	float	magnitude;
	t_vec3	b;

	magnitude = vec3_magnitude(a);
	if (magnitude < 0.00001)
		return (a);
	b.x = a.x / magnitude;
	b.y = a.y / magnitude;
	b.z = a.z / magnitude;
	return (b);
}
