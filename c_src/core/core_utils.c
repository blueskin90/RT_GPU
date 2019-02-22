/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 08:56:10 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/17 23:20:44 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	functional_function(t_huge *data, float delta, t_cam *cam)
{
	t_vec3 new_up;

	data->xdelta = (data->xpos - data->prevx) * delta * 10 * 2.0;
	data->ydelta = (data->ypos - data->prevy) * delta * 10 * 2.0;
	data->prevx = data->xpos;
	data->prevy = data->ypos;
	data->rotmat = matrix_mult(roty_matrix_init(data->xdelta),
		rotmatrix_axis_angle(cam->right, data->ydelta));
	new_up = vec3_normalize(matrix_mult_vec3(data->rotmat, cam->up));
	if (vec3_dot(new_up, vec3_init0(0, 1, 0)) >= 0)
	{
		cam->fw = vec3_normalize(matrix_mult_vec3(data->rotmat, cam->fw));
		cam->right = vec3_normalize(matrix_mult_vec3(data->rotmat, cam->right));
		cam->up = new_up;
	}
	cam->pos = vec3_add(cam->pos, vec3_mul(vec3_normalize(
		vec3_init0(cam->fw.x, 0, cam->fw.z)), data->f * 10 * delta));
	cam->pos = vec3_add(cam->pos, vec3_mul(cam->right, data->r * 10 * delta));
	cam->pos = vec3_add(cam->pos,
		vec3_mul(vec3_init0(0.0, 1.0, 0.0), data->u * 10 * delta));
}

void	transform_quadric_matrix(t_quadric *q, t_vec3 t)
{
	t_matrix translation;
	t_matrix transpose;

	translation = translation_matrix_init3(t);
	transpose = matrix_transpose(translation);
	q->matrix = matrix_mult(transpose, matrix_mult(q->matrix, translation));
}

void	sphere_torus(t_scene *scene)
{
	int			count;
	int			i;
	t_vec3		t;
	t_quadric	*q;

	count = 32;
	if (scene->quadric_count + count > NUMBER_OBJECT)
		return ;
	i = -1;
	while (++i < count)
	{
		q = &scene->quadrics[i + scene->quadric_count];
		init_material(q, i, count);
		q->matrix = identity_matrix_init();
		q->matrix.matrix[3][3] = -1;
		t.x = cos(i / (float)count * M_PI * 2) * 5;
		t.y = sin(i / (float)count * M_PI * 2) * 5;
		t.z = 0;
		transform_quadric_matrix(q, t);
		q->child_id = -1;
		q->negative = 0;
	}
	scene->quadric_count += count;
}

void	wows(t_huge *data, t_scenes **scenes)
{
	data->current_scene = fmin(data->current_scene, (*scenes)->scene_count - 1);
	data->current_cam = fmin(data->current_cam,
		(*scenes)->cam_count[data->current_scene] - 1);
	(*scenes)->scene[data->current_scene].mobius = data->wehaveafuckingmobius;
	(*scenes)->scene[data->current_scene].motion_blur = data->blur;
	UpdateBuffer(1, (*scenes)->scene + data->current_scene);
}
