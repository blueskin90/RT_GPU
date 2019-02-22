/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 13:50:21 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 06:18:42 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_one_objs(t_objs *obj)
{
	ft_printf("object id : %d combine : %s absolute: %d type : ", obj->id,
	obj->combine, obj->absolute);
	print_obj_type(obj->type);
	printf("\n");
	obj = obj->next;
}

void	print_t_objs(t_objs *obj, char *name)
{
	printf("%s LIST\n", name);
	while (obj)
	{
		ft_printf("object id : %d combine : %s absolute: %d type : ", obj->id,
		obj->combine, obj->absolute);
		print_obj_type(obj->type);
		printf("\n");
		obj = obj->next;
	}
	printf("\n");
}

void	print_matrix(t_matrix mat, int padding)
{
	(void)padding;
	printf("			[%7.3f, %7.3f, %7.3f, %7.3f] \n \
			[%7.3f, %7.3f, %7.3f, %7.3f] \n \
			[%7.3f, %7.3f, %7.3f, %7.3f] \n \
			[%7.3f, %7.3f, %7.3f, %7.3f]\n",
		mat.matrix[0][0], mat.matrix[0][1],
		mat.matrix[0][2],
		mat.matrix[0][3],
		mat.matrix[1][0],
		mat.matrix[1][1],
		mat.matrix[1][2],
		mat.matrix[1][3],
		mat.matrix[2][0],
		mat.matrix[2][1],
		mat.matrix[2][2],
		mat.matrix[2][3],
		mat.matrix[3][0],
		mat.matrix[3][1],
		mat.matrix[3][2],
		mat.matrix[3][3]);
}

void	print_common(t_transform trs, t_material mat)
{
	print_transform(trs, 5);
	print_material(mat, 5);
	if (mat.reflectance == -1)
		ft_printf("%*c %-10s : %-10s\n", 5, ' ', "light", "true");
	else
		ft_printf("%*c %-10s : %-10s\n", 5, ' ', "light", "false");
}

void	print_objects(t_scene scene)
{
	int		i;

	ft_printf("-----OBJECTS-----\n");
	i = -1;
	while (++i < scene.quadric_count)
		print_quadric(scene.quadrics[i], i);
	i = -1;
	while (++i < scene.capsule_count)
		print_capsule(scene.capsules[i], i);
	i = -1;
	while (++i < scene.torus_count)
		print_torus(scene.torus[i], i);
	i = -1;
	while (++i < scene.cube_count)
		print_cube(scene.cubes[i], i);
}
