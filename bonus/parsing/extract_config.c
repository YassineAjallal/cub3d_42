/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:21:12 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/15 17:04:38 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char **extract_textures(t_map *map)
{
	char **textures;
	t_map *head;
	int i;

	head = map;
	textures = malloc(sizeof(char *) * 6);
	while (head)
	{
		i = 2;
		if (head->cnofig == 'C')
		{
			if (!ft_strncmp(head->line, "NO", 2))
				textures[NO] = ft_strtrim(head->line + i, " \t");
			else if (!ft_strncmp(head->line, "SO", 2))
				textures[SO] = ft_strtrim(head->line + i, " \t");
			if (!ft_strncmp(head->line, "WE", 2))
				textures[WE] = ft_strtrim(head->line + i, " \t");
			else if (!ft_strncmp(head->line, "EA", 2))
				textures[EA] = ft_strtrim(head->line + i, " \t");
			else if (!ft_strncmp(head->line, "DO", 2))
				textures[DO] = ft_strtrim(head->line + i, " \t");
		}
		head = head->next;
	}
	textures[5] = NULL;
	return (textures);
}


