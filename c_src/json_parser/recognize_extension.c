/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_extension.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 22:50:35 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/17 23:09:06 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

void		check_file_extension(char *file)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (extension == NULL || ++extension == NULL)
		ft_error("No extension has been found\n");
	if (ft_strcmp(extension, "json"))
		ft_error("Bad extension to file. feed us JSON files\n");
}
