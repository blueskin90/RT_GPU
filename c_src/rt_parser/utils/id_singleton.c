/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_singleton.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 03:24:23 by toliver           #+#    #+#             */
/*   Updated: 2019/02/11 04:28:51 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			*get_ptr_obj_id(void)
{
	static int		id = 0;

	return (&id);
}

int					get_obj_id(void)
{
	return (*(get_ptr_obj_id()));
}

void				set_id(int nbr)
{
	int				*id;

	id = get_ptr_obj_id();
	(*id) = nbr;
}

void				add_id(int nbr)
{
	int				*id;

	id = get_ptr_obj_id();
	(*id) = nbr + (*id);
	if (*id >= NUMBER_OBJECTS)
		ft_error("To much objects found trough Id\n");
}
