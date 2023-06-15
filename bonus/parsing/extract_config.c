/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:21:12 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/12 14:44:05 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char **extract_textures(t_map *map)
{
	char **textures;
	t_map *head;
	int i;

	head = map;
	textures = malloc(sizeof(char *) * 5);
	while (head)
	{
		if (head->cnofig == 'C')
		{
			i = 2;
			while (head->line[i] == ' ')
				i++;
			if (!ft_strncmp(head->line, "NO", 2))
				textures[NO] = ft_strdup(head->line + i);
			else if (!ft_strncmp(head->line, "SO", 2))
				textures[SO] = ft_strdup(head->line + i);
			if (!ft_strncmp(head->line, "WE", 2))
				textures[WE] = ft_strdup(head->line + i);
			else if (!ft_strncmp(head->line, "EA", 2))
				textures[EA] = ft_strdup(head->line + i);
		}
		head = head->next;
	}
	textures[4] = NULL;
	return (textures);
}

// int convert_color(char *color_rgb)
// {
	
// }

// void extract_colors(t_map *map, t_cub *game)
// {
// 	t_map *head;
// 	int i;

// 	head = map;
// 	while (head)
// 	{
// 		if (head->cnofig == 'C')
// 		{
// 			i = 1;
// 			while (head->line[i] == ' ')
// 				i++;
// 			if (head->line[0] == 'F')
// 				game->floor_color = convert_color(head->line + i);
// 			else if (head->line[0] == 'C')	
// 				game->ciel_color = convert_color(head->line + i);
			
// 		}
// 		head = head->next;
// 	}
// }


