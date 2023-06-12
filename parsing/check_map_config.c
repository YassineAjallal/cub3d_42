/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 21:08:11 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/12 12:32:43 by yajallal         ###   ########.fr       */
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
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (a[i])
	{
		j = 0;
		if(a[i + 1])
			tmp = ft_strtrim(a[i], " \n");
		else
			tmp = ft_strtrim(a[i], "\n");
		while (tmp[j])
		{
			if (!ft_isdigit(tmp[j]))
			{
				free(tmp);
				return (0);
			}
			j++;
		}
		free(tmp);
		i++;
	}
	return (1);
}

void check_valid_config(t_map *config)
{
	t_map *tmp;
	char **split;

	tmp = config;
	while(tmp)
	{
		if (tmp->cnofig == 'C')
		{
			split = ft_split(tmp->line, ',');
			if (ft_isalpha(tmp->line[0]) == 0)
				error_print("invalid map\n");
			if (!ft_strcmp(split[0], "F") || !ft_strcmp(split[0], "C"))
			{
				if (array_len(split) != 4)
					error_print("invalid map\n");
				if(!allint(split))
					error_print("invalid map\n");
			}
		}
		tmp = tmp->next;
	}
}

void check_map_config(t_map *map)
{
	char **split;
	char **split_line;
	t_map *config;
	t_map *tmp;

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
				if (ft_strchr2d(split, split_line[0]) >= 0)
					config = delete_node(config, split_line[0]);
				else
					error_print("invalid map\n");
			}
			else
				error_print("invalid map\n");
		}
		map = map->next;
	}
	map = tmp;
	check_valid_config(map);
}
