/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 14:22:57 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/10 18:56:46 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			bad_limits_float(float min, float max, float value, char *key)
{
	if (key)
		ft_dprintf(2, "value of %s is %f but should be between %f and %f \n",
				key, value, min, max);
	else
		ft_dprintf(2, "value of (?) is %f but should be between %f and %f \n",
				value, min, max);
	exit(0);
}

void			bad_limits_int(int min, int max, int value, char *key)
{
	if (key)
		ft_dprintf(2, "value of %s is %d but should be between %d and %d \n",
				key, value, min, max);
	else
		ft_dprintf(2, "value of (?) is %d but should be between %d and %d \n",
				value, min, max);
	exit(0);
}

void			missing_in_json(char *key, char *parent)
{
	if (parent)
		ft_dprintf(2, "the key %s is missing in %s\n", key, parent);
	else
		ft_dprintf(2, "the key %s is missing\n", key);
	exit(0);
}

void			is_req_in_config(char *key, char *parent)
{
	if (parent)
		ft_dprintf(2, "the key %s is required in %s\n", key, parent);
	else
		ft_dprintf(2, "the key %s is required\n", key);
	exit(0);
}
