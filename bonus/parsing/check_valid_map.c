/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:02:14 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 16:24:42 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	space_border(char **map, int i, int j)
{
	if (j + 1 > ft_strlen(map[i - 1]) || !ft_strchr("0NSEW1", map[i - 1][j]))
		return (0);
	if (j + 1 > ft_strlen(map[i + 1]) || !ft_strchr("0NSEW1", map[i + 1][j]))
		return (0);
	if (!ft_strchr("0NSEW1", map[i][j - 1]))
		return (0);
	if (!ft_strchr("0NSEW1", map[i][j + 1]))
		return (0);
	return (1);
}

int	map_closed(char **map)
{
	int	i;
	int	len;
	int	j;

	i = 1;
	len = ft_strlen2d(map);
	while (i < len - 1)
	{
		j = 1;
		if (!first_last_wall(map[i]))
			return (0);
		while (map[i][j] && map[i][j] != '\n')
		{
			if (ft_strchr("0NSEW", map[i][j]))
			{
				if (!space_border(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_valid_map(char **map)
{
	int	len;

	len = ft_strlen2d(map);
	if (!check_walls(map[0]) || !check_walls(map[len - 1]))
		return (0);
	else if (!check_characters(map))
		return (0);
	else if (!map_closed(map))
		return (0);
	return (1);
}
