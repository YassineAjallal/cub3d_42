/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:21:12 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/15 16:42:24 by yajallal         ###   ########.fr       */
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

// char *extract_texture_name(char *texture)
// {
	
// }

char **extract_textures(t_map *map)
{
	char **textures;
	t_map *head;
	int i;

	head = map;
	textures = malloc(sizeof(char *) * 5);
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


