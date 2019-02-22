/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 12:24:41 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/17 19:31:20 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	char		*parse_scene_name(t_elem *parent_elem,
		t_elem *config)
{
	t_elem			*elem;
	char			*str;

	config = get_child_config("name", config);
	elem = extract_child(parent_elem, config, "name", 1);
	str = json_parse_string(elem, config);
	return (ft_strdup(str));
}

static int			rt_parsing_get_nbr_scene(t_temp_scenes *temp_scenes,
						t_elem *config, t_elem *begin)
{
	int				nbr_scene;
	t_elem			*child_config;
	t_elem			*curr;

	nbr_scene = 0;
	child_config = get_child_config("scene", config);
	curr = extract_child(begin, child_config, NULL, 1);
	if (curr == NULL && SCENE_REQUIRED)
		ft_error(SCENE_IS_REQUIRED);
	while (curr && nbr_scene < NUMBER_SCENES)
	{
		temp_scenes->scene[nbr_scene] = parse_scene(curr, child_config);
		temp_scenes->scene_name[nbr_scene] = parse_scene_name(curr,
			child_config);
		parse_cameras(temp_scenes, nbr_scene, curr, child_config);
		temp_scenes->scene_count = nbr_scene + 1;
		nbr_scene++;
		curr = curr->next;
	}
	return (nbr_scene);
}

void				rt_parsing_normalizator(t_scenes *scenes)
{
	(void)scenes;
}

t_scenes			*rt_parsing(t_elem *begin)
{
	t_scenes		*scenes;
	t_temp_scenes	*temp_scenes;
	t_elem			*config;
	t_elem			*config_begin;
	int				nbr_scene;

	temp_scenes = ft_malloc(sizeof(t_temp_scenes));
	config_begin = json_parser("c_src/rt_parser/config/config.json");
	config = extract_config_child(config_begin, "first element");
	if (config == NULL)
		ft_error("missing scenes in config file");
	config = get_config_by_key(config, "scenes", NULL);
	check_req_type(begin, config);
	nbr_scene = rt_parsing_get_nbr_scene(temp_scenes, config, begin);
	scenes = ft_malloc(sizeof(t_scenes));
	merge_temp_scenes_to_scenes(temp_scenes, scenes);
	check_nbr_elements(nbr_scene, config);
	free_elem(begin);
	free_elem(config_begin);
	free(temp_scenes);
	rt_parsing_normalizator(scenes);
	if (VERBOSE_SCENE == 1)
		print_scenes(scenes);
	return (scenes);
}
