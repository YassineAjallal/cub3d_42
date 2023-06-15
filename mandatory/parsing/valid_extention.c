/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_extention.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:52:29 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/01 18:35:39 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void valid_extention(char *map_file)
{
	int len;

	len = ft_strlen(map_file) - 4;
	if (ft_strcmp(map_file + len, ".cub"))
		error_print("invalid extention\n");
}