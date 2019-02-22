/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:37:40 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/17 22:33:37 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			change_position(t_json json, t_objs *master)
{
	t_elem	*elem;

	elem = json_get_key(json.elem, json.config, "position");
	if (elem != NULL)
		((t_default *)master->obj)->transform.pos =
			parse_vec3(json.elem, json.config, "position");
}

static void		adapt_quadric(t_objs *master)
{
	t_temp_quadric	*tmp;

	tmp = (t_temp_quadric *)master->obj;
	tmp->rot_mat = parse_rotation_matrix((tmp)->transform.rot);
	tmp->trans_mat = parse_translation_matrix((tmp)->transform.pos);
	tmp->transformation_matrix =
			matrix_mult((tmp)->rot_mat, tmp->trans_mat);
}

void			change_rotation(t_json json, t_objs *master)
{
	t_elem			*elem;
	t_vec3			temp;

	elem = json_get_key(json.elem, json.config, "rotation");
	if (elem != NULL)
	{
		if (master->type == CUBE || master->type == TORUS
				|| master->type == CAPSULE)
		{
			temp = parse_vec3_to_rad(json.elem, json.config, "rotation");
			((t_default *)master->obj)->transform.rot = qeuler(temp);
		}
		else
		{
			temp = parse_vec3(json.elem, json.config, "rotation");
			((t_default *)master->obj)->transform.rot =
					vec4_init0(temp.x, temp.y, temp.z, 0.0);
		}
	}
	if (is_quadric(master->type))
		adapt_quadric(master);
}

t_objs			*parse_copy(t_json json, t_temp_scene *scene,
					t_objs **parent, t_objs **tree)
{
	t_objs	*master;
	char	*key;
	int		nbr_name;
	t_objs	*temp;

	key = json_string(json.elem, json.config, "name");
	if (!ft_strcmp(key, ""))
		ft_error("Copy type does not have an existing name\n");
	nbr_name = number_of_objs_with_name(tree, key);
	if (nbr_name > 1)
		ft_error("More than one object has been found with the same name");
	else if (nbr_name == 0)
	{
		ft_dprintf(2, "No object has been found with the name : %s\n", key);
		exit(0);
	}
	master = get_obj_by_name(tree, key);
	master = parse_object((t_json){.elem = master->json.elem,
				.config = master->json.config}, scene, parent, tree);
	temp = get_obj_by_id(*tree, master->id);
	temp->name = NULL;
	master->name = NULL;
	change_position(json, master);
	change_rotation(json, master);
	return (master);
}
