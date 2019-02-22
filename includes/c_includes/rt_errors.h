/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaulaus <apaulaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:21:48 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/12 11:56:56 by apaulaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERRORS_H
# define RT_ERRORS_H

/*
**	WRONG FORMAT
*/
# define FIRST_ELEM_BAD_FORMAT "FIRST ELEMENT MUST BE ARRAY\n"
# define SCENE_BAD_FORMAT "Wrong format for SCENE, must be OBJECT\n"
# define SCENE_NAME_BAD_FORMAT "Wrong format for NAME, must be STRING\n"
# define OBJECTS_BAD_FORMAT "Wrong format for OBJECTS, must be OBJECT type\n"
# define VECTOR_BAD_FORMAT "Wrong format for VECTOR, must be OBJECT type\n"
# define SPHERES_BAD_FORMAT "Wrong format for SPHERES, must be STRING type\n"
# define SPHERE_BAD_FORMAT "Bad format for elems of SPHERES, must be OBJECT\n"
# define X_BAD_FORMAT "Wrong format for "
# define X_SHOULD_NOT_BE " should not be "
# define X_MUST_BE "must be \n"
# define BAD_FORMAT_HEX "hex in color should be a valid hexadecimal\n"
# define HEX_NOT_IN_LIMIT "Hex is to big or to small to enter color spectrum \n"
# define RADIUS_BAD_FORMAT "Radius of object should be higher than 0\n"
# define BRILLANCE_BAD_FORMAT "Brillance must be between 1 and 128 included\n"
# define SPECULAR_BAD_FORMAT "Specular must be between 0 and 1 included\n"
# define DIFFUSE_BAD_FORMAT "Diffuse must be between 0 and 1 included\n"
# define AMBIANT_BAD_FORMAT "Ambiant must be between 0 and 1 included\n"
# define FOV_BAD_FORMAT "FOV must be between ]0 and 180[ excluded\n"
# define ITENSITITY_BAD_FORMAT "Itensity must be between 0 and 1 included\n"

/*
** INFORMATION REQUIRED
*/
# define IS_REQUIRED " is required\n"
# define AT_LEAST_ONE_REQUIRED "at least one "
# define SCENE_IS_REQUIRED "At least one SCENE is required\n"
# define NAME_IS_REQUIRED "Name is required\n"
# define SPHERES_IS_REQUIRED "Spheres is required\n"
# define ONE_SPHERE_IS_REQUIRED "At least one SPHERE is required\n"
# define OBJECTS_IS_REQUIRED "Their must be at least one object in your SCENE\n"
# define VECTOR_IS_REQUIRED "Vector is required\n"
# define MATRIX_REQUIRED "Matrix is required\n"
# define VECTOR_POINT_IS_REQUIRED "Vector point is required \n"
# define CANNOT_POSITION "Cannot determine vectors of obj whitout pos\n"

/*
** WRONG VALUES
*/
# define LOOKAT_DIRECTION_CONFLICT "Lookat and direction given and not equal\n"
# define DIR_CANNOT_POINT_0 "Direction cannot point (0,0,0)\n"
# define LOOKAT_CANNOT_POINT_0 "vec between Lookat & pos cannot point (0,0,0)\n"
# define RGB_BAD_VAL "RGB values must be between 0 and 255\n"
# define RGB_HEX_CONFLICT "RGB and HEX given but value are different\n"
/*
**# define ROLL_RIGHT_UP_CONFLICT "Right Roll & UP where given but dont match\n"
**# define RIGHT_UP_CONFLICT "Right And UP where given but angle is not 90deg\n"
**# define RIGHT_ROLL_CONFLICT "Right and Roll where given but dont match\n"
**# define UP_ROLL_CONFLICT "UP and Roll where given but dont match\n"
**# define UP_DIR_CONFLICT "Up is given but bad angle with dir\n"
**# define RIGHT_DIR_CONFLICT "Right is given but bad angle with dir\n"
**# define DIRECTION_CONFLICT "Direction CONFLICT on UP RIGHT DIR\n"
*/
#endif
