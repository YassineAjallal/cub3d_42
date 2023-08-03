/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:11:24 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 16:53:04 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_map	*add_new_node(char *line, char config, t_map *map)
{
	t_map	*head;
	t_map	*new_node;

	head = map;
	new_node = malloc(sizeof(t_map));
	if (!new_node)
		return (NULL);
	new_node->line = ft_strdup(line);
	new_node->cnofig = config;
	new_node->next = NULL;
	if (!map)
		map = new_node;
	else
	{
		while (head->next)
			head = head->next;
		head->next = new_node;
	}
	return (map);
}

t_map	*delete_head(t_map *head, char *str)
{
	t_map	*remove;

	remove = head;
	head = head->next;
	free(remove->line);
	remove->line = NULL;
	free(remove);
	remove = NULL;
	return (head);
}

t_map	*delete_node(t_map *head, char *str)
{
	t_map	*node;
	t_map	*remove;

	node = head;
	if (!head)
		return (NULL);
	if (!ft_strcmp(head->line, str))
		return (delete_head(head, str));
	while (node->next)
	{
		if (!ft_strcmp(node->line, str))
		{
			remove = node->next;
			node->next = node->next->next;
			free(remove->line);
			remove->line = NULL;
			free(remove);
			remove = NULL;
		}
		if (node->next)
			node = node->next;
	}
	return (head);
}

size_t	lst_size(t_map *config)
{
	int		len;
	t_map	*node;

	len = 0;
	node = config;
	while (node)
	{
		len++;
		node = node->next;
	}
	return (len);
}

t_map	*free_list(t_map *map)
{
	t_map	*node;
	t_map	*remove;

	node = map;
	if (!map)
		return (NULL);
	while (node)
	{
		remove = node;
		node = node->next;
		free(remove->line);
		remove->line = NULL;
		free(remove);
		remove = NULL;
	}
	map = NULL;
	return (map);
}
