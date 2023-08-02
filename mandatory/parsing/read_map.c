/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:38:31 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/02 23:01:36 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print(t_map *map)
{
	t_map	*head;

	head = map;
	while (head)
	{
		ft_putchar_fd(head->cnofig, 1);
		ft_putstr_fd(" : ", 1);
		ft_putstr_fd(head->line, 1);
		head = head->next;
	}
}

t_map	*read_map(char *map_file)
{
	int		map_fd;
	char	*line;
	t_map	*map;
	int		i;

	map = NULL;
	map_fd = open(map_file, O_RDONLY);
	if (map_fd < 0)
	{
		ft_malloc(0, 0, 'C');
		error_print("file not found\n");
	}
	line = get_next_line(map_fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (ft_strlen(line + i) != 0)
		{
			if (line[0] == '1' || line[0] == ' ')
				break ;
			map = add_new_node(line, 'C', map, 'B');
		}
		line = get_next_line(map_fd);
	}
	while (line)
	{
		map = add_new_node(line, 'M', map, 'A');
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (map);
}
