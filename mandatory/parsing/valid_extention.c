/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_extention.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:52:29 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/31 17:32:35 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	valid_extention(char *map_file)
{
	int	len;

	len = ft_strlen(map_file) - 4;
	if (ft_strcmp(map_file + len, ".cub"))
		error_print("invalid extention\n");
}
