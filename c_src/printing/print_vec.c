/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 05:08:35 by toliver           #+#    #+#             */
/*   Updated: 2019/02/11 05:10:40 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		print_vec4(t_vec4 vec4, int padding)
{
	ft_printf("%*c %10s : %10f\n", padding, ' ', "x", vec4.x);
	ft_printf("%*c %10s : %10f\n", padding, ' ', "y", vec4.y);
	ft_printf("%*c %10s : %10f\n", padding, ' ', "z", vec4.z);
	ft_printf("%*c %10s : %10f\n", padding, ' ', "w", vec4.w);
}

void		print_vec3(t_vec3 vec3, int padding)
{
	ft_printf("%*c %10s : %10f\n", padding, ' ', "x", vec3.x);
	ft_printf("%*c %10s : %10f\n", padding, ' ', "y", vec3.y);
	ft_printf("%*c %10s : %10f\n", padding, ' ', "z", vec3.z);
}
