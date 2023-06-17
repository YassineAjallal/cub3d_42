/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:16:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/16 19:00:42 by yajallal         ###   ########.fr       */
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
	int map_len;
	t_map *node;
	int i;
	char **map_array;

	node = map;
	i = 0;
	check_map_config(map, game);
	map_len = get_map_len(map);
	if (map_len == 0)
		return (NULL);
	map_array = malloc(sizeof(char *) * (map_len + 1));
	if (!map_array)
		return (NULL);
	while (node)
	{
		if (node->cnofig == 'M')
		{
			map_array[i] = node->line;
			i++;
		}
		node = node->next;
	}
	map_array[i] = NULL;
	return (map_array);
}
