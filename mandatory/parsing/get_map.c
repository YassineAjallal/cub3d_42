/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:16:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 13:02:14 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_map_len(t_map *map)
{
	t_map *node;
	int map_len;

	node = map;
	map_len = 0;
	while(node)
	{
		if (node->cnofig == 'M')
			map_len++;
		node = node->next;
	}
	return (map_len);
}

char **get_map(t_map *map, t_cub *game)
{
	t_map *node;
	int i;
	char **map_array;

	node = map;
	i = 0;
	check_map_config(map, game);
	game->map_len = get_map_len(map);
	if (game->map_len == 0)
		return (NULL);
	map_array = malloc(sizeof(char *) * (game->map_len + 1));
	if (!map_array)
		return (NULL);
	while (node)
	{
		if (node->cnofig == 'M')
		{
			map_array[i] = ft_strdup(node->line);
			i++;
		}
		node = node->next;
	}
	map_array[i] = NULL;
	free_list(map);
	return (map_array);
}

int get_large_line(t_cub *game)
{
	int i;
	int large_line;

	i = 0;
	large_line = 0;
	if (game->map)
	{
		large_line = ft_strlen(game->map[i]);
		while(game->map[i])	
		{
			if ( ft_strlen(game->map[i]) > large_line)
				large_line = ft_strlen(game->map[i]);
			i++;
		}
	}
	return (large_line);
}
