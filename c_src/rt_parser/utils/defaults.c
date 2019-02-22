/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:45:42 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 03:33:42 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rgb		default_rgb(t_rgb rgb, t_rgb def)
{
	if (rgb.r == INFINITY)
		rgb.r = def.r;
	if (rgb.g == INFINITY)
		rgb.g = def.g;
	if (rgb.b == INFINITY)
		rgb.b = def.b;
	return (rgb);
}
