/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 21:08:11 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/15 17:04:47 by yajallal         ###   ########.fr       */
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
	if (config_len != 7)
		error_print("incomplet map\n");
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

int	array_len(char **array)
{
	int i;

	i = 0;
	while(array[i])
		i++;
	return (i);
}

int	allint(char **a)
{
	int i = 1;
	char *tmp;
	int len;
	int j;

	while (i < 4)
	{
		len = ft_strlen(a[i]);
		if ((!ft_strchr(a[i], ',') && i != 3) || (i == 3 && ft_strchr(a[i], ','))
			|| ft_strlen(a[i]) > 4)
			error_print("invalid colors\n");
		else if (a[i][len - 1] == ',' && !ft_isdigit(a[i][len - 2]))
			error_print("invalid colors\n");
		else
		{
			j = 0;
			tmp = ft_strtrim(a[i], ",");
			while(tmp[j])
				if (!ft_isdigit(tmp[j++]))
					error_print("invalid colors\n");
			if (ft_atoi(tmp) > 255 || ft_atoi(tmp) < 0)
				error_print("invalid colors\n");
		}
		i++;
	}
	return (rgba(ft_atoi(a[1]), ft_atoi(a[2]), ft_atoi(a[3]), 1));
}

void check_valid_config(t_map *config, t_cub *game)
{
	t_map *tmp;
	char **split;

	tmp = config;
	while(tmp)
	{
		if (tmp->cnofig == 'C')
		{
			if (tmp->line[0] == 'F' || tmp->line[0] == 'C')
			{
				split = ft_split(tmp->line, ' ');
				if (array_len(split) != 4)
					error_print("invalid colors\n");
				if (tmp->line[0] == 'F')
					game->floor_color = allint(split);
				else
					game->ciel_color = allint(split);
			}
		}
		tmp = tmp->next;
	}
}

void check_map_config(t_map *map, t_cub *game)
{
	char **split;
	char **split_line;
	t_map *config;
	t_map *tmp;

	config_len(map);
	tmp = map;
	split = ft_split("NO SO WE EA DO F C", ' ');
	config = config_list(split);
	while (map)
	{
		if (map->cnofig == 'C')
		{
			if (map->line[0] != ' ')
			{
				split_line = ft_split(map->line, ' ');
				if (ft_strchr2d(split, split_line[0]) >= 0)
					config = delete_node(config, split_line[0]);
				else
					error_print("invalid config\n");
			}
			else
				error_print("invalid config\n");
		}
		map = map->next;
	}
	map = tmp;
	check_valid_config(map, game);
}
