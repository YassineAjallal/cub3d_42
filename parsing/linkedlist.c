/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:11:24 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/01 19:19:53 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_map *add_new_node(char *line, char config,t_map *map)
{
	t_map *head;
	t_map *new_node;

	head = map;
	new_node = malloc(sizeof(t_map));
	if (!new_node)
		return (NULL);
	new_node->line = line;
	new_node->cnofig = config;
	new_node->next = NULL;
	if (!map)
		map = new_node;
	else
	{
		while(head->next)
			head = head->next;
		head->next = new_node;
	}
	return(map);
}