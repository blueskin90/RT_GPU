/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <cvermand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:03:05 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/17 22:48:44 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

static int		key_cmp(t_elem *elem)
{
	t_elem	*next;

	while (elem && elem->next)
	{
		next = elem->next;
		while (next)
		{
			if (ft_strcmp(elem->key, next->key) == 0)
				json_error(SAME_KEY_NAME);
			next = next->next;
		}
		elem = elem->next;
	}
	return (0);
}

static int		check_for_same_key_in_object(t_elem *begin)
{
	t_elem	*current;
	t_elem	*child;

	child = NULL;
	current = begin;
	while (current)
	{
		if (current->type == OBJECT)
		{
			if (current->value.objecty)
			{
				child = (t_elem *)current->value.objecty;
				key_cmp(child);
				check_for_same_key_in_object(child);
			}
		}
		if (current->type == ARRAY)
			if (current->value.arrayi)
			{
				child = (t_elem *)current->value.arrayi;
				check_for_same_key_in_object(child);
			}
		current = current->next;
	}
	return (0);
}

static void		check_end_of_json_file(char **line, int fd)
{
	int ret;

	if ((*line))
		free((*line));
	(*line) = NULL;
	add_line_number(1);
	if ((ret = ft_get_next_line(fd, line)) != 0)
		json_error(END_OF_FILE_BAD_FORMAT);
	if ((*line))
		free((*line));
	(*line) = NULL;
}

static void		check_json_integrity(char *line, int fd, t_elem *begin)
{
	check_end_of_json_file(&line, fd);
	check_for_same_key_in_object(begin);
	check_end_of_json_file(&line, fd);
}

t_elem			*json_parser(char *file)
{
	int		fd;
	char	*line;
	int		ret;
	t_elem	*begin;
	int		x;

	check_file_extension(file);
	set_line_number(1);
	begin = create_elem();
	line = NULL;
	x = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		json_error(FD_FAIL);
	if ((ret = ft_get_next_line(fd, &line)) != 1)
		json_error(EMPTY_FILE);
	if (line[0] == '{')
		json_recognize_object(begin, &line, &x, fd);
	else if (line[0] == '[')
		json_recognize_array(begin, &line, &x, fd);
	else
		json_error(BAD_BEGIN_OF_FILE);
	check_json_integrity(line, fd, begin);
	print_tree_and_close(begin, fd);
	return (begin);
}
