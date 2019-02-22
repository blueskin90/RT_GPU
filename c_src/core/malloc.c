/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:33:50 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 05:29:49 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				*ft_malloc(size_t size)
{
	void			*ptr;

	if (!(ptr = malloc(size)))
		ft_error("MALLOC FAILED");
	ft_bzero(ptr, size);
	return (ptr);
}
