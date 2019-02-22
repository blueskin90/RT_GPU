/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 04:47:51 by toliver           #+#    #+#             */
/*   Updated: 2019/02/11 04:50:05 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_temp_quadric(t_temp_quadric quadric, int quad_nbr)
{
	ft_printf("------------------------------\n");
	ft_printf("%*c %-10s %-10d\n", 5, ' ', "quadric", quad_nbr + 1);
	ft_printf("------------------------------\n");
	ft_printf("%*c %-10s\n", 5, ' ', "matrix");
	print_matrix(quadric.matrix, 10);
	print_material(quadric.material, 10);
	ft_printf("%*c %-10s :\n", 10, ' ', "position");
	print_vec3(quadric.transform.pos, 15);
	ft_printf("%*c child id : %d\n", 10, ' ', quadric.child_id);
	ft_printf("%*c is a negative : %d\n", 10, ' ', quadric.negative);
}

void	print_quadric(t_quadric quadric, int quad_nbr)
{
	ft_printf("------------------------------\n");
	ft_printf("%*c %-10s %-10d\n", 5, ' ', "quadric", quad_nbr + 1);
	ft_printf("------------------------------\n");
	ft_printf("%*c %-10s\n", 5, ' ', "matrix");
	print_matrix(quadric.matrix, 10);
	print_material(quadric.material, 10);
	ft_printf("%*c child id : %d\n", 10, ' ', quadric.child_id);
	ft_printf("%*c is a negative : %d\n", 10, ' ', quadric.negative);
}

void	print_cube(t_cube cube, int cube_nbr)
{
	ft_printf("------------------------------\n");
	ft_printf("%*c %-10s %-10d\n", 5, ' ', "cube", cube_nbr + 1);
	ft_printf("------------------------------\n");
	ft_printf("%*c %-10s :\n", 5, ' ', "size");
	ft_printf("%*c child id : %d\n", 10, ' ', cube.child_id);
	ft_printf("%*c is a negative : %d\n", 10, ' ', cube.negative);
	print_vec3(cube.size, 10);
	print_common(cube.transform, cube.material);
}

void	print_torus(t_torus torus, int torus_nbr)
{
	ft_printf("------------------------------\n");
	ft_printf("%*c %-10s %-10d\n", 5, ' ', "torus", torus_nbr + 1);
	ft_printf("------------------------------\n");
	ft_printf("%*c %-10s : %10f\n", 5, ' ', "major radius", torus.major_radius);
	ft_printf("%*c %-10s : %10f\n", 5, ' ', "minor radius", torus.minor_radius);
	print_common(torus.transform, torus.material);
}

void	print_capsule(t_capsule capsule, int capsule_nbr)
{
	ft_printf("------------------------------\n");
	ft_printf("%*c %-10s %-10d\n", 5, ' ', "capsule", capsule_nbr + 1);
	ft_printf("------------------------------\n");
	ft_printf("%*c %-10s : %10f\n", 5, ' ', "z", capsule.z);
	ft_printf("%*c %-10s : %10f\n", 5, ' ', "radius", capsule.radius);
	print_common(capsule.transform, capsule.material);
}
