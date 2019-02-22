/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 17:28:27 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 05:16:23 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_transform(t_transform trs, int padding)
{
	ft_printf("%*c %-10s :\n", padding, ' ', "position");
	print_vec3(trs.pos, padding + 5);
	ft_printf("%*c %-10s :\n", padding, ' ', "rotation");
	print_vec4(trs.rot, padding + 5);
}
