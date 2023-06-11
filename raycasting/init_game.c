/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:17:54 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/11 17:56:13 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void find_player(t_cub *game)
{
	int i = 0;
	int j;

	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->p_coord.x = j;
				game->p_coord.y = i;
				if(game->map[i][j] == 'N')
					game->player_angle = 3 * M_PI / 2;
				else if(game->map[i][j] == 'S')
					game->player_angle = M_PI / 2;
				else if(game->map[i][j] == 'E')
					game->player_angle = 0;
				else if(game->map[i][j] == 'W')
					game->player_angle = M_PI;
				return;
			}
			j++;
		}
		i++;
	}
}

int rgba(int r, int g, int b, float t)
{
	int hex = (r << 24) | (g << 16) | (b << 8) | (int)(t * 255);
	return hex;
}

void parseImage(mlx_texture_t *img, int arr[512 * 512])
{
	unsigned int i = 0;
	unsigned int j = 0;
	while (i < (img->width * img->height) * img->bytes_per_pixel)
	{
		arr[j] = rgba(img->pixels[i], img->pixels[i + 1], img->pixels[i + 2], 1);
		j++;
		i += img->bytes_per_pixel;
	}
}

void init_game(t_cub *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", 0);
	game->wallN = mlx_load_png("../images/photo-pngrepo-com.png");
	game->wallS = mlx_load_png("../images/1.png");
	game->wallW = mlx_load_png("../images/brick-wall-wall-pngrepo-com.png");
	game->wallE = mlx_load_png("../images/magnifying-glass-pngrepo-com.png");
	game->map_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->map_img, 0, 0);
	parseImage(game->wallN, game->textures->color_arrayN);
	parseImage(game->wallS, game->textures->color_arrayS);
	parseImage(game->wallW, game->textures->color_arrayW);
	parseImage(game->wallE, game->textures->color_arrayE);
	find_player(game);
}

