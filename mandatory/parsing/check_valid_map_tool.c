/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map_tool.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:24:28 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 16:25:06 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_walls(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' && line[i])
		i++;
	if (line[i] == '\n')
		return (0);
	return (1);
}

int	check_characters(char **map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (ft_strchr("01NSEW ", map[i][j]))
			{
				if (ft_strchr("NSEW", map[i][j]))
					player++;
			}
			else
				return (0);
			j++;
		}
		i++;
	}
	if (player != 1)
		return (0);
	return (1);
}

int	first_last_wall(char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, "\n ");
	if (tmp[0] != '1' || tmp[ft_strlen(tmp) - 1] != '1')
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}
