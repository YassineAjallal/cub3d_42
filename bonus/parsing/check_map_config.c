/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:10:34 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 16:22:35 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	is_color(t_map *map, t_map *tmp, t_cub *game)
{
	char	*tmp_str;
	char	**split;

	tmp_str = ft_strtrim(tmp->line + 1, " \t");
	if (!color_formatting(tmp_str))
	{
		free(tmp_str);
		free_list(map);
		error_print("invalid colors\n");
	}
	split = ft_split(tmp_str, ',');
	free(tmp_str);
	if (array_len(split) != 3)
	{
		ft_free2d(split);
		free_list(map);
		error_print("invalid colors\n");
	}
	if (tmp->line[0] == 'F')
		game->floor_color = allint(split, map);
	else
		game->ciel_color = allint(split, map);
	ft_free2d(split);
}

void	check_valid_color(t_map *map, t_cub *game)
{
	t_map	*tmp;
	char	**split;
	char	*tmp_str;

	tmp = map;
	while (tmp)
	{
		if (tmp->cnofig == 'C')
		{
			if (tmp->line[0] == 'F' || tmp->line[0] == 'C')
				is_color(map, tmp, game);
		}
		tmp = tmp->next;
	}
}

t_map	*texutre_color_checker(t_map *map, t_map *config, char **split)
{
	char	**split_line;

	if (map->cnofig == 'C')
	{
		if (map->line[0] != ' ')
		{
			split_line = ft_split(map->line, ' ');
			config = delete_node(config, split_line[0]);
			ft_free2d(split_line);
		}
		else
		{
			ft_free2d(split);
			free_list(map);
			error_print("invalid config\n");
		}
	}
	return (config);
}

void	check_map_config(t_map *map, t_cub *game)
{
	char	**split;
	char	**split_line;
	t_map	*config;
	t_map	*tmp;

	config_len(map);
	tmp = map;
	split = ft_split("NO SO WE EA F C", ' ');
	config = config_list(split);
	while (map)
	{
		config = texutre_color_checker(map, config, split);
		map = map->next;
	}
	if (lst_size(config) > 0)
	{
		ft_free2d(split);
		free_list(config);
		free_list(map);
		error_print("invalid config\n");
	}
	ft_free2d(split);
	map = tmp;
	check_valid_color(map, game);
}
