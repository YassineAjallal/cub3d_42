/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:21:12 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 16:26:55 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	calc_space(char *str)
{
	int	space;
	int	i;

	i = 0;
	space = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			space++;
		i++;
	}
	return (space);
}

char	**extract_textures(t_map *map)
{
	char	**textures;
	t_map	*head;

	head = map;
	textures = malloc(sizeof(char *) * 5);
	if (!textures)
		return (NULL);
	while (head)
	{
		if (head->cnofig == 'C')
		{
			if (!ft_strncmp(head->line, "NO", 2))
				textures[NO] = ft_strtrim(head->line + 2, " \t");
			else if (!ft_strncmp(head->line, "SO", 2))
				textures[SO] = ft_strtrim(head->line + 2, " \t");
			if (!ft_strncmp(head->line, "WE", 2))
				textures[WE] = ft_strtrim(head->line + 2, " \t");
			else if (!ft_strncmp(head->line, "EA", 2))
				textures[EA] = ft_strtrim(head->line + 2, " \t");
		}
		head = head->next;
	}
	textures[4] = NULL;
	free_list(map);
	return (textures);
}
