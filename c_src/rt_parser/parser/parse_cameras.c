/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cameras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:59:45 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 05:06:20 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int				get_filter_name(char *str)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(str, "no filter"))
		return (NO_FILTER);
	else if (!compare(str, "sepia"))
		return (SEPIA);
	else if (!compare(str, "black and white"))
		return (BLACK_AND_WHITE);
	return (NO_FILTER);
}

static t_cam			parse_camera(t_elem *elem, t_elem *config)
{
	t_cam	cam;
	float	roll;
	t_elem	*child_elem;
	t_elem	*child_config;

	cam.pos = parse_vec3(elem, config, "position");
	cam.fw = parse_vec3(elem, config, "forward");
	if (cam.fw.x < 0.00001 && cam.fw.x >= 0.0
		&& cam.fw.y < 0.00001 && cam.fw.y >= 0.0
		&& cam.fw.z < 0.00001 && cam.fw.z >= 0.0)
		ft_error("Forward of camera can not be (0.0, 0.0, 0.0)\n");
	cam.fw = vec3_norm(cam.fw);
	roll = json_float(elem, config, "roll");
	cam.right = get_right_dir(cam.fw);
	cam.right = vec_rot_zaxis_angle(cam.right, cam.fw, roll);
	cam.up = get_up_dir(cam.fw, cam.right);
	cam.fov = json_float(elem, config, "fov");
	cam.focal_length = json_float(elem, config, "focal_length");
	cam.aperture = json_float(elem, config, "aperture");
	cam.picasso = json_bool(elem, config, "picasso");
	cam.swirl = json_bool(elem, config, "swirl");
	child_config = get_child_config("filter", config);
	child_elem = extract_child(elem, child_config, "filter", 1);
	cam.filter = get_filter_name(json_parse_string(child_elem, child_config));
	return (cam);
}

void					parse_cameras(t_temp_scenes *scenes, int nbr_scene,
							t_elem *parent_elem, t_elem *config)
{
	t_elem	*elem;
	t_elem	*cam_elem;
	t_elem	*child_config;
	t_elem	*cam_config;
	int		cam_nbr;

	cam_nbr = 0;
	child_config = get_child_config("cameras", config);
	elem = extract_child(parent_elem, child_config, "cameras", 1);
	if (elem)
	{
		cam_config = get_child_config("camera", child_config);
		cam_elem = extract_child(elem, cam_config, NULL, 1);
		while (cam_elem && cam_nbr < NUMBER_CAMERAS)
		{
			scenes->cam[nbr_scene][cam_nbr] =
					parse_camera(cam_elem, cam_config);
			scenes->cam_count[nbr_scene] = cam_nbr + 1;
			cam_elem = cam_elem->next;
			cam_nbr++;
		}
	}
	check_nbr_elements(cam_nbr, child_config);
}
