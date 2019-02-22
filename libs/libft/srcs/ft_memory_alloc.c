/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:03:48 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/27 18:03:50 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memory_alloc(size_t size)
{
	void	*result;
	size_t	i;

	result = malloc(size);
	if (!result)
		return (NULL);
	i = 0;
	while (i < size)
	{
		((char *)result)[i] = 0;
		i++;
	}
	return (result);
}
