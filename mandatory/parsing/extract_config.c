/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:21:12 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/02 18:41:53 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int calc_space(char *str)
{
	int space;
	int i;

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

char **extract_textures(t_map *map)
{
	char **textures;
	t_map *head;
	int i;

	head = map;
	textures = ft_malloc(sizeof(char *) * 5, 1, 'A');
	while (head)
	{
		i = 2;
		if (head->cnofig == 'C')
		{
			if (!ft_strncmp(head->line, "NO", 2))
				textures[NO] = ft_strtrim_tool(head->line + i, " \t", 'A');
			else if (!ft_strncmp(head->line, "SO", 2))
				textures[SO] = ft_strtrim_tool(head->line + i, " \t", 'A');
			if (!ft_strncmp(head->line, "WE", 2))
				textures[WE] = ft_strtrim_tool(head->line + i, " \t", 'A');
			else if (!ft_strncmp(head->line, "EA", 2))
				textures[EA] = ft_strtrim_tool(head->line + i, " \t", 'A');
		}
		head = head->next;
	}
	textures[4] = NULL;
	return (textures);
}


