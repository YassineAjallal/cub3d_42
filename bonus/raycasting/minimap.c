/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:43:26 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/14 17:48:48 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

// void draw_rays(t_cub *game)
// {
// 	float angle = game->player_angle - FOV_ANGLE / 2;
//     float end_angle = game->player_angle + FOV_ANGLE / 2;
// 	t_coord target_coord;


// 	while (angle < end_angle)
// 	{
// 		target_coord.x = game->p_coord.x + cos(angle) * 500;
// 		target_coord.y = game->p_coord.y + sin(angle) * 500;
// 		drawline(game->p_coord, target_coord, game, 0xFF0000FF);
// 		angle += 0.001;
// 	}
// }

// void	drw_wall(int h, int w, t_cub *game)
// {
// 	int i = h;
// 	while (i < h + 40)
// 	{
// 		int j = w;
// 		while (j < w + 40)
// 		{
// 			if (i == h + 39 || i == h || j == w + 39 || j == w)
// 				mlx_put_pixel(game->map_img, j, i, 0x00000000);
// 			else
// 				mlx_put_pixel(game->map_img, j, i, 0xFFFFFFFF);
// 			j++;
// 		}
		
// 		i++;
// 	}
	
// }
// void	draw_maps(t_cub *game)
// {
// 	int i = 0;
// 	while (i < 20)
// 	{
// 		int j = 0;
// 		while (j < 10)
// 		{
// 			if(game->map[i][j] == '1')
// 				drw_wall(i * 40, j * 40, 0xFFFFFFAA);
// 			else
// 				drw_wall(i * 40, j * 40,0x00000000);
// 			j++;
// 		}
		
// 		i++;
// 	}
// }
// void drw_pixels(t_cub *game)
// {
// 	draw_maps(game);
// 	draw_rays(game);
// }

// int main()
// {
// 	cub.mlx = mlx_init(NUM_RAYS, height, "CUB3D", 0);

// 	cub.map = mlx_new_image(cub.mlx, NUM_RAYS, height);
// 	mlx_image_to_window(cub.mlx, cub.map, 0, 0);
// 	draw_maps();
// 	find_player();

// 	mlx_loop_hook(cub.mlx, hooks,NULL);
// 	mlx_loop(cub.mlx);
// 	mlx_terminate(cub.mlx);
// 	return (0);
// }