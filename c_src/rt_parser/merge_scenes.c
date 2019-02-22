/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_scenes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 07:18:38 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 07:40:20 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_quadric		merge_quadrics(t_temp_quadric quad)
{
	t_quadric			new_quadric;
	t_matrix			mat_mult;
	t_matrix			transpose;

	new_quadric.material = quad.material;
	transpose = matrix_transpose(quad.transformation_matrix);
	mat_mult = matrix_mult(quad.matrix, quad.transformation_matrix);
	new_quadric.matrix = matrix_mult(transpose, mat_mult);
	new_quadric.child_id = quad.child_id;
	new_quadric.negative = quad.negative;
	return (new_quadric);
}

void			new_scenes_counts(t_temp_scenes *sc, t_scenes *new_scenes,
				int nbr_scenes)
{
	new_scenes->scene[nbr_scenes].cube_count =
		sc->scene[nbr_scenes].cube_count;
	new_scenes->scene[nbr_scenes].torus_count =
		sc->scene[nbr_scenes].torus_count;
	new_scenes->scene[nbr_scenes].capsule_count =
		sc->scene[nbr_scenes].capsule_count;
	new_scenes->scene[nbr_scenes].quadric_count =
		sc->scene[nbr_scenes].quadric_count;
	new_scenes->scene[nbr_scenes].light_count =
		sc->scene[nbr_scenes].light_count;
}

static void		new_scenes_forms(t_temp_scenes *sc, t_scenes *new_scenes,
				int nbr_scenes)
{
	int			i;

	i = -1;
	while (++i < sc->scene[nbr_scenes].cube_count)
		new_scenes->scene[nbr_scenes].cubes[i] = sc->scene[nbr_scenes].cubes[i];
	i = -1;
	while (++i < sc->scene[nbr_scenes].torus_count)
		new_scenes->scene[nbr_scenes].torus[i] = sc->scene[nbr_scenes].torus[i];
	i = -1;
	while (++i < sc->scene[nbr_scenes].capsule_count)
		new_scenes->scene[nbr_scenes].capsules[i] =
			sc->scene[nbr_scenes].capsules[i];
	i = -1;
	while (++i < sc->scene[nbr_scenes].quadric_count)
		new_scenes->scene[nbr_scenes].quadrics[i] =
				merge_quadrics(sc->scene[nbr_scenes].quadrics[i]);
}

static void		new_scenes_cams(t_temp_scenes *sc, t_scenes *ns, int nbr_scenes)
{
	int			i;

	i = -1;
	while (++i < sc->cam_count[nbr_scenes])
		ns->cam[nbr_scenes][i] = sc->cam[nbr_scenes][i];
	i = -1;
	while (++i < sc->cam_count[nbr_scenes])
		ns->cam_count[nbr_scenes] = sc->cam_count[nbr_scenes];
}

void			merge_temp_scenes_to_scenes(t_temp_scenes *sc, t_scenes *ns)
{
	int			nbr_scenes;
	int			i;

	nbr_scenes = 0;
	ns->scene_count = sc->scene_count;
	while (nbr_scenes < sc->scene_count)
	{
		new_scenes_counts(sc, ns, nbr_scenes);
		new_scenes_forms(sc, ns, nbr_scenes);
		new_scenes_cams(sc, ns, nbr_scenes);
		i = -1;
		while (++i < sc->scene_count)
			ns->scene_name[i] = sc->scene_name[i];
		i = -1;
		while (++i < sc->scene_count)
		{
			ns->scene[i].sun_dir = sc->scene[i].sun_dir;
			ns->scene[i].ambient_light_color = sc->scene[i].ambient_light_color;
		}
		i = -1;
		while (++i < sc->scene[nbr_scenes].light_count)
			ns->scene[nbr_scenes].lights[i] = sc->scene[nbr_scenes].lights[i];
		nbr_scenes++;
	}
}
