/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_config_tool.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:10:11 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 16:23:23 by yajallal         ###   ########.fr       */
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

int	allint(char **a, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (a[i][j])
		{
			if (!ft_isdigit(a[i][j++]))
			{
				free_list(map);
				error_print("invalid colors\n");
			}
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

int	color_formatting(char *color)
{
	int	i;

	i = 0;
	if (color[0] == ',' || color[ft_strlen(color) - 1] == ',')
		return (0);
	while (color[i])
	{
		if (color[i] == ',' && color[i + 1] == ',')
			return (0);
		i++;
	}
	return (1);
}
