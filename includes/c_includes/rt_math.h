/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:06:42 by apaulaus          #+#    #+#             */
/*   Updated: 2019/02/11 05:47:03 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H

# include <math.h>
# include "libftg.h"

t_vec4			qmult(t_vec4 q1, t_vec4 q2);
t_vec3			mulone(t_vec3 a, float b);
t_vec3			cross(t_vec3 a, t_vec3 b);

#endif
