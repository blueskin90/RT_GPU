/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:11:56 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/10 18:42:20 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_elem		*get_array_elem(t_elem *elem)
{
	return (elem->value.arrayi);
}

void		check_nbr_elements(int nbr_elems, t_elem *config)
{
	json_min_max_int(nbr_elems, config);
}
