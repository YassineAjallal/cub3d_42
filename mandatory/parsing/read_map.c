/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:38:31 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/31 17:31:59 by mkhairou         ###   ########.fr       */
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
		error_print("file not found\n");
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
			map = add_new_node(line, 'C', map);
		}
		else
			free(line);
		line = get_next_line(map_fd);
	}
	while (line)
	{
		map = add_new_node(line, 'M', map);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (map);
}

// int main(int ac, char *av[])
// {
// 	t_map *map;
// 	int i;
// 	char **map_arr;

// 	i = 0;
// 	(void)ac;
// 	map = read_map(av[1]);
// 	check_map_config(map);
// 	map_arr = get_map(map);
// 	if (!check_valid_map(map_arr))
// 		printf("1 : Error\n");
// 	return (0);
// }
