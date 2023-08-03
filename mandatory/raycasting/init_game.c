/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:17:54 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 13:11:52 by yajallal         ###   ########.fr       */
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
void free_colors(t_cub *game)
{
	if (game->textures->color_arrayE)
		free(game->textures->color_arrayE);
	if(game->textures->color_arrayN)
		free(game->textures->color_arrayN);
	if(game->textures->color_arrayW)
		free(game->textures->color_arrayW);
	if(game->textures->color_arrayS)
		free(game->textures->color_arrayS);
}

int	alloc_textures(t_cub *game)
{
	game->textures->color_arrayE = ft_malloc(sizeof(int) * (game->wallE->height
				* game->wallE->width), 1, 'A');
	game->textures->color_arrayN = ft_malloc(sizeof(int) * (game->wallN->height
				* game->wallN->width), 1, 'A');
	game->textures->color_arrayW = ft_malloc(sizeof(int) * (game->wallW->height
				* game->wallW->width), 1, 'A');
	game->textures->color_arrayS = ft_malloc(sizeof(int) * (game->wallS->height
				* game->wallS->width), 1, 'A');
	if (!game->textures->color_arrayE || !game->textures->color_arrayN
		|| !game->textures->color_arrayW || !game->textures->color_arrayS)
		return (0);
	return (1);
}
void free_texturs(t_cub *game)
{
	if (game->wallE)
		free(game->wallE);
	if (game->wallN)
		free(game->wallN);
	if (game->wallS)
		free(game->wallS);
	if (game->wallW)
		free(game->wallW);
}

int	init_game(t_cub *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", 0);
	game->wallN = mlx_load_png(game->textures_img[NO]);
	game->wallS = mlx_load_png(game->textures_img[SO]);
	game->wallW = mlx_load_png(game->textures_img[WE]);
	game->wallE = mlx_load_png(game->textures_img[EA]);
	ft_free2d(game->textures_img);
	if (!game->wallE || !game->wallS || !game->wallN || !game->wallW)
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
	parse_image(game->wallN, game->textures->color_arrayN);
	parse_image(game->wallS, game->textures->color_arrayS);
	parse_image(game->wallW, game->textures->color_arrayW);
	parse_image(game->wallE, game->textures->color_arrayE);
	find_player(game);
	return (1);
}
