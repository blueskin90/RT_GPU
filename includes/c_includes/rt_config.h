/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_config.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:04:23 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 05:46:27 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CONFIG_H
# define RT_CONFIG_H

typedef struct	s_key_float
{
	int			required;
	float		min_value;
	float		max_value;
	int			min_included;
	int			max_included;
	float		default_value;
	char		*name;
	char		*types[3];
}				t_key_float;

#endif
