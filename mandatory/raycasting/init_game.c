/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:17:54 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 15:50:51 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	find_player(t_cub *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (ft_strchr("NSEW", game->map[i][j]))
			{
				game->p_coord.x = j;
				game->p_coord.y = i;
				if (game->map[i][j] == 'N')
					game->player_angle = 3 * M_PI / 2;
				else if (game->map[i][j] == 'S')
					game->player_angle = M_PI / 2;
				else if (game->map[i][j] == 'E')
					game->player_angle = 0;
				else if (game->map[i][j] == 'W')
					game->player_angle = M_PI;
				return ;
			}
		}
	}
}

int	rgba(int r, int g, int b, float t)
{
	int	hex;

	hex = (r << 24) | (g << 16) | (b << 8) | (int)(t * 255);
	return (hex);
}

void	parse_image(mlx_texture_t *img, int *arr)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < (img->width * img->height) * img->bytes_per_pixel)
	{
		arr[j] = rgba(img->pixels[i], img->pixels[i + 1], img->pixels[i + 2],
				1);
		j++;
		i += img->bytes_per_pixel;
	}
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

int	alloc_textures(t_cub *game)
{
	game->textures->color_arraye = malloc(sizeof(int) * (game->walle->height
				* game->walle->width));
	game->textures->color_arrayn = malloc(sizeof(int) * (game->walln->height
				* game->walln->width));
	game->textures->color_arrayw = malloc(sizeof(int) * (game->wallw->height
				* game->wallw->width));
	game->textures->color_arrays = malloc(sizeof(int) * (game->walls->height
				* game->walls->width));
	if (!game->textures->color_arraye || !game->textures->color_arrayn
		|| !game->textures->color_arrayw || !game->textures->color_arrays)
		return (0);
	return (1);
}

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

int	init_game(t_cub *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", 0);
	game->walln = mlx_load_png(game->textures_img[NO]);
	game->walls = mlx_load_png(game->textures_img[SO]);
	game->wallw = mlx_load_png(game->textures_img[WE]);
	game->walle = mlx_load_png(game->textures_img[EA]);
	ft_free2d(game->textures_img);
	if (!game->walle || !game->walls || !game->walln || !game->wallw)
	{
		free_texturs(game);
		error_print("image error\n");
	}
	game->map_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!alloc_textures(game))
	{
		free_colors(game);
		free_texturs(game);
		return (0);
	}
	mlx_image_to_window(game->mlx, game->map_img, 0, 0);
	parse_image(game->walln, game->textures->color_arrayn);
	parse_image(game->walls, game->textures->color_arrays);
	parse_image(game->wallw, game->textures->color_arrayw);
	parse_image(game->walle, game->textures->color_arraye);
	find_player(game);
	return (1);
}
