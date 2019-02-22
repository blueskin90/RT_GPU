/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_required_information.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaulaus <apaulaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 21:54:40 by toliver           #+#    #+#             */
/*   Updated: 2019/02/12 11:57:13 by apaulaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_REQUIRED_INFORMATION_H
# define RT_REQUIRED_INFORMATION_H

# define SCENE_REQUIRED 1
# define NAME_REQUIRED 0
# define OBJECTS_REQUIRED 1
# define VECTOR_REQUIRED 0
# define VECTOR_POINT_REQUIRED 0
# define ONE_SPHERE_REQUIRED 1
# define SPHERES_REQUIRED 0
# define CONES_REQUIRED 0
# define PLANES_REQUIRED 0
# define CYLINDERS_REQUIRED 0
# define LIGHTS_REQUIRED 0
# define SPHERE_RADIUS_REQUIRED 1
# define CYLINDER_RADIUS_REQUIRED 1
# define PLANE_ANGLE_REQUIRED 1
# define CONE_ANGLE_REQUIRED 1

/*
**	CAMERAS
*/

# define CAMERAS_REQUIRED 1
# define CAMERA_POSITION 1
# define CAMERA_FORWARD 0
# define CAMERA_ROLL 0

# define CAMERA_FOV 0
# define CAMERA_APERTURE 0
# define CAMERA_FOCAL_LENGTH 0
# define CAMERA_FILTER 0

/*
** OBJECTS
*/

# define POSITION_REQUIRED 1
# define LOOKAT_REQUIRED 0
# define DIRECTION_REQUIRED 0
# define LOOKAT_OR_DIRECTION_REQUIRED 1
# define ROLL_OR_UP_OR_RIGHT_REQUIRED 1
# define TRANSLATION_REQUIRED 0
# define ROTATION_REQUIRED 0
# define DIR_REQUIRED 0
# define ROLL_REQUIRED 0
# define INTENSITY_REQUIRED 1
# define FOV_REQUIRED 1

/*
**# define UP_REQUIRED 0
**# define RIGHT_REQUIRED 0
*/

/*
** COLORS
*/
# define COLOR_REQ 0
# define DIFFUSE_REQ 0
# define SPECULAR_REQ 0
# define BRILLANCE_REQ 0
# define AMBIANT_REQ 0
# define COLOR_RGB_REQUIRED 0
# define COLOR_HEX_REQUIRED 0
# define COLOR_AT_LEAST_ONE_REQUIRED 0
# define AMBIANT_REQUIRED 0
#endif
