/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaulaus <apaulaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 19:46:50 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 06:53:50 by apaulaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			print_rgb(t_rgb c, int padding)
{
	ft_printf("%*c %10s : %10f\n", padding, ' ', "r", c.r);
	ft_printf("%*c %10s : %10f\n", padding, ' ', "g", c.g);
	ft_printf("%*c %10s : %10f\n", padding, ' ', "b", c.b);
	ft_printf("%*c %10s : %10x\n", padding, ' ', "val", c.value);
}

void			print_color(t_vec3 vec3, int padding)
{
	ft_printf("%*c %10s : %10f\n", padding, ' ', "r", vec3.x);
	ft_printf("%*c %10s : %10f\n", padding, ' ', "g", vec3.y);
	ft_printf("%*c %10s : %10f\n", padding, ' ', "b", vec3.z);
}

void			print_mode_type(t_texture_type type)
{
	if (type == NO_TEXTURE)
		ft_printf("NO_TEXTURE");
	if (type == PLAIN_TEXTURE)
		ft_printf("PLAIN_TEXTURE");
	if (type == TRANSPARENCE_TEXTURE)
		ft_printf("TRANSPARENCE_TEXTURE");
	if (type == NORMAL_MAP)
		ft_printf("NORMAL_MAP");
	if (type == CHECKERBOARD)
		ft_printf("CHECKERBOARD");
	if (type == RIPPLE_EFFECT)
		ft_printf("RIPPLE_EFFECT");
	if (type == SPIRAL)
		ft_printf("SPIRAL");
	if (type == PERLIN)
		ft_printf("PERLIN");
	ft_printf("\n");
}

void			print_material(t_material mat, int padding)
{
	ft_printf("%*c %-10s :\n", padding, ' ', "color");
	print_color(mat.color, padding + 5);
	ft_printf("%*c %-10s : %10f\n", padding, ' ', "reflectance",
		mat.reflectance);
	ft_printf("%*c %-10s : %10f\n", padding, ' ', "refraction_index",
		mat.refraction_index);
	ft_printf("%*c %-10s : %10f\n", padding, ' ', "opacity", mat.opacity);
	ft_printf("%*c %-10s : %10f\n", padding, ' ', "roughness", mat.roughness);
	ft_printf("%*c %-10s : %10d.png\n", padding, ' ', "texture",
		mat.texture_id);
	if (mat.mode >= 0)
		ft_printf("%*c %-10s : %10s\n", padding, ' ', "mapping", "spherical");
	else
		ft_printf("%*c %-10s : %10s\n", padding, ' ', "mapping", "planar");
	ft_printf("%*c %-10s : %10f\n", padding, ' ', "stretch", mat.stretch);
	ft_printf("%*c %-10s : %10f\n", padding, ' ', "shift", mat.shift);
	ft_printf("%*c %-10s : ", padding, ' ', "texture mode");
	print_mode_type(abs(mat.mode));
}
