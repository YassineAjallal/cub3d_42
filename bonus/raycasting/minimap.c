/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:43:26 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/01 15:12:28 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	pixel_draw_mini(t_coord c0, t_coord c1, t_cub *game, int color)
{
	if (c0.x >= 0 && c0.x < game->large_length * TILE 
		&& c0.y >= 0 && c0.y < game->map_len * TILE)
		mlx_put_pixel(game->map_img, c0.x * SCALE_MINIMAP,
			c0.y * SCALE_MINIMAP, color);
}

void	drawline_mini(t_coord c0, t_coord c1, t_cub *game, int color)
{
	t_coord	d;
	t_coord	s;
	int		err;
	int		err2;

	s = init_drawline(c0, c1);
	d.x = abs((int)c1.x - (int)c0.x);
	d.y = abs((int)c1.y - (int)c0.y);
	err = d.x - d.y;
	while ((int)floorf(c0.x) != (int)floorf(c1.x) 
		|| (int)floorf(c0.y) != (int)floorf(c1.y))
	{
		pixel_draw_mini(c0, c1, game, color);
		err2 = 2 * err;
		if (err2 > -d.y)
		{
			err -= d.y;
			c0.x += s.x;
		}
		if (err2 < d.x)
		{
			err += d.x;
			c0.y += s.y;
		}
	}
}

void	draw_wall(int h, int w, t_cub *game, int color)
{
	int	i;
	int	j;

	i = h;
	while (i <= h + TILE)
	{
		j = w;
		while (j <= w + TILE)
		{
			mlx_put_pixel(game->map_img, i * SCALE_MINIMAP, 
				j * SCALE_MINIMAP, color);
			j++;
		}
		i++;
	}
}

void	draw_maps(t_cub *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
				draw_wall(j * TILE, i * TILE, game, rgba(255, 255, 255, 1));
			else if (game->map[i][j] == '0' || game->map[i][j] == ' ' ||
				ft_strchr("ESNW", game->map[i][j]) || game->map[i][j] == '2')
				draw_wall(j * TILE, i * TILE, game, rgba(0, 0, 0, 1));
			else if (game->map[i][j] == 'D')
				draw_wall(j * TILE, i * TILE, game, rgba(25, 25, 255, 1));
			j++;
		}
		i++;
	}
}

void	put_minimap(t_cub *game)
{
	draw_maps(game);
	rays_minimap(game);
}
