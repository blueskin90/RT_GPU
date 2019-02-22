/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:06:45 by toliver           #+#    #+#             */
/*   Updated: 2019/02/11 09:53:12 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_matrix		identity_matrix_init(void)
{
	t_matrix	id;

	id.matrix[0][0] = 1.0;
	id.matrix[0][1] = 0.0;
	id.matrix[0][2] = 0.0;
	id.matrix[0][3] = 0.0;
	id.matrix[1][0] = 0.0;
	id.matrix[1][1] = 1.0;
	id.matrix[1][2] = 0.0;
	id.matrix[1][3] = 0.0;
	id.matrix[2][0] = 0.0;
	id.matrix[2][1] = 0.0;
	id.matrix[2][2] = 1.0;
	id.matrix[2][3] = 0.0;
	id.matrix[3][0] = 0.0;
	id.matrix[3][1] = 0.0;
	id.matrix[3][2] = 0.0;
	id.matrix[3][3] = 1.0;
	return (id);
}

t_matrix		init_full_matrix(t_vec4 a, t_vec4 b, t_vec4 c, t_vec4 d)
{
	t_matrix	id;

	id.matrix[0][0] = a.x;
	id.matrix[0][1] = a.y;
	id.matrix[0][2] = a.z;
	id.matrix[0][3] = a.w;
	id.matrix[1][0] = b.x;
	id.matrix[1][1] = b.y;
	id.matrix[1][2] = b.z;
	id.matrix[1][3] = b.w;
	id.matrix[2][0] = c.x;
	id.matrix[2][1] = c.y;
	id.matrix[2][2] = c.z;
	id.matrix[2][3] = c.w;
	id.matrix[3][0] = d.x;
	id.matrix[3][1] = d.y;
	id.matrix[3][2] = d.z;
	id.matrix[3][3] = d.w;
	return (id);
}

t_matrix		scale_matrix_init(float scale)
{
	t_matrix	scalematrix;

	scalematrix = identity_matrix_init();
	scalematrix.matrix[0][0] *= scale;
	scalematrix.matrix[1][1] *= scale;
	scalematrix.matrix[2][2] *= scale;
	return (scalematrix);
}

t_matrix		translation_matrix_init3(t_vec3 tranvec)
{
	t_matrix	translationmatrix;

	translationmatrix = identity_matrix_init();
	translationmatrix.matrix[0][3] = tranvec.x;
	translationmatrix.matrix[1][3] = tranvec.y;
	translationmatrix.matrix[2][3] = tranvec.z;
	return (translationmatrix);
}

t_matrix		translation_matrix_init4(t_vec4 tranvec)
{
	t_matrix	translationmatrix;

	translationmatrix = identity_matrix_init();
	translationmatrix.matrix[0][3] = tranvec.x;
	translationmatrix.matrix[1][3] = tranvec.y;
	translationmatrix.matrix[2][3] = tranvec.z;
	return (translationmatrix);
}
