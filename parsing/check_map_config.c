/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 21:08:11 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/01 21:43:24 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int ft_strchr2d(char **str2d, char *str)
{
	int i;

	i = 0;
	while(str2d[i])
	{
		if (!ft_strcmp(str2d[i], str))
			return i;
		i++;
	}
	return (-1);
}
void config_len(t_map *map)
{
	int config_len;

	config_len = 0;
	while(map)
	{
		if (map->cnofig == 'C')
			config_len++;
		map = map->next;
	}
	if (config_len != 6)
		error_print("invalid map\n");
}
t_map *config_list(char **split)
{
	int  i;
	t_map *config;
	
	config = NULL;
	i = 0;
	while(split[i])
	{
		config = add_new_node(split[i], 'C', config);
		i++;
	}
	return (config);
}

void check_map_config(t_map *map)
{
	char **split;
	char **split_line;
	t_map *config;

	config_len(map);
	split = ft_split("NO SO WE EA F C", ' ');
	config = config_list(split);
	while (map)
	{
		split_line = ft_split(map->line, ' ');
		if (map->cnofig == 'C')
		{
			if (ft_strchr2d(split, split_line[0]) >= 0)
			{
				config = delete_node(config, split_line[0]);
			}
			else
				error_print("invalid map\n");
		}
		map = map->next;
	}
}