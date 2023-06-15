/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_positions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:34:07 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/15 17:43:29 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
int calc_d(char **map)
{
	int i;
	int j;
	int nb_d;

	i = 0;
	nb_d = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == 'D')
				nb_d++;
			j++;
		}
		i++;
	}
	return (nb_d);
}

int *d_positions(char **map)
{
	int i;
	int j;
	int k;
	int nb_d;
	int *d_pos;

	i = 0;
	k = 0;
	nb_d = calc_d(map);
	d_pos = malloc(sizeof(int) * (nb_d * 2));
	if (!d_pos)
		return (NULL);
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == 'D')
			{
				d_pos[k] = i;
				d_pos[k + 1] = j;
				k += 2;
			}
			j++;
		}
		i++;
	}
	return (d_pos);
}
