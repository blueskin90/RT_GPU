/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 05:42:45 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 08:00:46 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec4			qmult(t_vec4 q1, t_vec4 q2)
{
	t_vec4		q;

	q.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
	q.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
	q.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);
	q.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
	return (q);
}

t_vec4			qconjugate(t_vec4 q)
{
	t_vec4		temp;

	temp.x = -1;
	temp.y = -1;
	temp.z = -1;
	temp.w = 1;
	return (vec4_hadamard(q, temp));
}

t_vec3			qmulvec(t_vec3 v, t_vec4 q)
{
	t_vec3		temp;
	t_vec3		rot;

	rot = (t_vec3){
		.x = q.x,
		.y = q.y,
		.z = q.z
	};
	temp = vec3_mul(vec3_crossproduct(rot, vec3_add(vec3_crossproduct(rot, v)
					, vec3_mul(v, q.w))), 2.0);
	return (vec3_add(v, temp));
}

t_vec4			vec4_hadamard(t_vec4 a, t_vec4 b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}
