/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:50:58 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 17:53:16 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	free_texturs(t_cub *game)
{
	if (game->walle)
		mlx_delete_texture(game->walle);
	if (game->walln)
		mlx_delete_texture(game->walln);
	if (game->walls)
		mlx_delete_texture(game->walls);
	if (game->wallw)
		mlx_delete_texture(game->wallw);
}

void	free_colors(t_cub *game)
{
	if (game->textures->color_arraye)
		free(game->textures->color_arraye);
	if (game->textures->color_arrayn)
		free(game->textures->color_arrayn);
	if (game->textures->color_arrayw)
		free(game->textures->color_arrayw);
	if (game->textures->color_arrays)
		free(game->textures->color_arrays);
}
