/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 21:08:11 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 11:38:57 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strchr_lst(char **str2d, char *str)
{
	int	i;

	i = 0;
	while (str2d[i])
	{
		if (!ft_strcmp(str2d[i], str))
			return (i);
		i++;
	}
	return (-1);
}

void	config_len(t_map *map)
{
	int	config_len;

	config_len = 0;
	while (map)
	{
		if (map->cnofig == 'C')
			config_len++;
		map = map->next;
	}
	if (config_len != 6)
	{
		free_list(map);
		error_print("incomplet map\n");
	}
}

t_map	*config_list(char **split)
{
	int		i;
	t_map	*config;

	config = NULL;
	i = 0;
	while (split[i])
	{
		config = add_new_node(split[i], 'C', config);
		i++;
	}
	return (config);
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	allint(char **a, t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (a[i][j])
			if (!ft_isdigit(a[i][j++]))
			{
				free_list(map);
				error_print("invalid colors\n");
			}
		if (ft_atoi(a[i]) > 255 || ft_atoi(a[i]) < 0)
		{
			free_list(map);
			error_print("invalid colors\n");
		}
		i++;
	}
	return (rgba(ft_atoi(a[0]), ft_atoi(a[1]), ft_atoi(a[2]), 1));
}
int color_formatting(char *color)
{
	int i;

	i = 0;
	if (color[0] == ',' || color[ft_strlen(color) - 1] == ',')
		return (0);
	while(color[i])
	{
		if (color[i] == ',' && color[i + 1] == ',')
			return (0);
		i++;
	}
	return (1);
}

void	check_valid_config(t_map *map, t_cub *game)
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
			{
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
		}
		tmp = tmp->next;
	}
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
	check_valid_config(map, game);
}
