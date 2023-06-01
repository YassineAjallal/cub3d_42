/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:38:31 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/01 19:26:15 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void print(t_map *map)
{
	t_map *head;

	head = map;
	while(head)
	{
		printf("%c : %s",head->cnofig ,head->line);
		head = head->next;
	}
}
t_map *read_map_config(char *map_file)
{
	int map_fd;
	char *line;
	t_map *map_config;

	map_config = NULL;
	map_fd = open(map_file, O_RDONLY);
	if (map_fd < 0)
		error_print("file not found\n");
	line = get_next_line(map_fd);
	while(line)
	{
		if (ft_strcmp(line, "\n"))
		{
			if (line[0] == '1' || line[0] == ' ')
				break;
			map_config = add_new_node(line, 'C',map_config);

		}
		else
			free(line);
		line = get_next_line(map_fd);
	}
	while(line)
	{
		map_config = add_new_node(line, 'M', map_config);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (map_config);
}

int main(int ac, char *av[])
{
	t_map *map_config;
	t_map *map_texture;

	map_config = read_map_config(av[1]);
	print(map_config);
	return 0;
}
