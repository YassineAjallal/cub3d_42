/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:25:33 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/23 15:58:16 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void key_up(t_cub *game)
{
	// float playercos = cos(game->player_angle) * 0.1;
	// float playersin = sin(game->player_angle) * 0.1;
	// float tmpx = game->p_coord.x + playercos;
	// float tmpy = game->p_coord.y + playersin;
	// if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
	// {
	// 	game->p_coord.y = tmpy;
	// 	game->p_coord.x = tmpx;

	// }
	if(game->map[(int)floorf(game->p_coord.y)][(int)floorf(game->p_coord.x + game->dda->dirx * 0.1)] != '1') 
		game->p_coord.x += game->dda->dirx * 0.1;
    if(game->map[(int)floorf(game->p_coord.y + game->dda->diry)][(int)floorf(game->p_coord.x)] != '1') 
		game->p_coord.y += game->dda->diry * 0.1;

	ray_cast(game);
}

void key_down(t_cub *game)
{
	// float playercos = cos(game->player_angle) * 0.1;
	// float playersin = sin(game->player_angle) * 0.1;
	// float tmpx = game->p_coord.x - playercos;
	// float tmpy = game->p_coord.y - playersin;
	// if (game->map[(int)floorf(tmpy + 0.1)][(int)floorf(tmpx + 0.1)] != '1')
	// {
	// 	game->p_coord.y = tmpy;
	// 	game->p_coord.x = tmpx;

	// }
	if(game->map[(int)floorf(game->p_coord.y)][(int)floorf(game->p_coord.x - game->dda->dirx * 0.1)] != '1') 
		game->p_coord.x -= game->dda->dirx * 0.1;
    if(game->map[(int)floorf(game->p_coord.y - game->dda->diry)][(int)floorf(game->p_coord.x)] != '1') 
		game->p_coord.y -= game->dda->diry * 0.1;
	ray_cast(game);
}

void key_A(t_cub *game)
{
	// game->player_angle -= 0.05;
	// if (game->player_angle < 0)
	// 	game->player_angle += 2 * M_PI;
	// else if (game->player_angle > 2 * M_PI)
	// 	game->player_angle -= 2 * M_PI;
	double oldDirX = game->dda->dirx;
	game->dda->dirx = game->dda->dirx * cos(0.05) - game->dda->diry * sin(0.05);
	game->dda->diry = oldDirX * sin(0.05) + game->dda->diry * cos(0.05);
	double oldPlaneX = game->dda->planex;
	game->dda->planex = game->dda->planex * cos(0.05) - game->dda->planey * sin(0.05);
	game->dda->planey = oldPlaneX * sin(0.05) + game->dda->planey * cos(0.05);
	ray_cast(game);
}
void key_D(t_cub *game)
{
	// game->player_angle += 0.05;
	// if (game->player_angle < 0)
	// 	game->player_angle += 2 * M_PI;
	// else if (game->player_angle > 2 * M_PI)
	// 	game->player_angle -= 2 * M_PI;
	double oldDirX = game->dda->dirx;
	game->dda->dirx = game->dda->dirx * cos(-0.05) - game->dda->diry * sin(-0.05);
	game->dda->diry = oldDirX * sin(-0.05) + game->dda->diry * cos(-0.05);
	double oldPlaneX = game->dda->planex;
	game->dda->planex = game->dda->planex * cos(-0.05) - game->dda->planey * sin(-0.05);
	game->dda->planey = oldPlaneX * sin(-0.05) + game->dda->planey * cos(-0.05);
	ray_cast(game);
}
// void key_A(t_cub *game)
// {
//     double oldDirX = game->dda->dirx;
//     game->dda->dirx = game->dda->dirx * cos(0.05) - game->dda->diry * sin(0.05);
//     game->dda->diry = oldDirX * sin(0.05) + game->dda->diry * cos(0.05);
//     double oldPlaneX = game->dda->planex;
//     game->dda->planex = game->dda->planex * cos(0.05) - game->dda->planey * sin(0.05);
//     game->dda->planey = oldPlaneX * sin(0.05) + game->dda->planey * cos(0.05);
//     ray_cast(game);
// }

// void key_D(t_cub *game)
// {
//     double oldDirX = game->dda->dirx;
//     game->dda->dirx = game->dda->dirx * cos(-0.05) - game->dda->diry * sin(-0.05);
//     game->dda->diry = oldDirX * sin(-0.05) + game->dda->diry * cos(-0.05);
//     double oldPlaneX = game->dda->planex;
//     game->dda->planex = game->dda->planex * cos(-0.05) - game->dda->planey * sin(-0.05);
//     game->dda->planey = oldPlaneX * sin(-0.05) + game->dda->planey * cos(-0.05);
//     ray_cast(game);
// }

void hooks(void *ptr)
{
	t_cub *game = (t_cub *)ptr;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		key_up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		key_down(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		key_A(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		key_D(game);
}