/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:25:33 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/29 19:05:00 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void key_up(t_cub *game)
{
	float playercos = cos(game->player_angle) * 0.1;
	float playersin = sin(game->player_angle) * 0.1;
	float tmpx = game->p_coord.x + playercos;
	float tmpy = game->p_coord.y + playersin;
	if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
	{
		game->p_coord.y = tmpy;
		game->p_coord.x = tmpx;
		put_minimap(game);
	}
	// ray_cast(game);
}

void key_down(t_cub *game)
{
	float playercos = cos(game->player_angle) * 0.1;
	float playersin = sin(game->player_angle) * 0.1;
	float tmpx = game->p_coord.x - playercos;
	float tmpy = game->p_coord.y - playersin;
	if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
	{
		game->p_coord.y = tmpy;
		game->p_coord.x = tmpx;
		put_minimap(game);
	}
	// ray_cast(game);
}

void key_A(t_cub *game)
{
	game->player_angle -= 0.05;
	if (game->player_angle < 0)
		game->player_angle += 2 * M_PI;
	else if (game->player_angle > 2 * M_PI)
		game->player_angle -= 2 * M_PI;
	// ray_cast(game);
	put_minimap(game);
}
void key_D(t_cub *game)
{
	game->player_angle += 0.05;
	if (game->player_angle < 0)
		game->player_angle += 2 * M_PI;
	else if (game->player_angle > 2 * M_PI)
		game->player_angle -= 2 * M_PI;
	// ray_cast(game);
	put_minimap(game);
}

void	open_door(t_cub *game)
{
	int i;
	float playercos = cos(game->player_angle) * 1;
	float playersin = sin(game->player_angle) * 1;
	float tmpx = game->p_coord.x + playercos;
	float tmpy = game->p_coord.y + playersin;
	if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] == 'D')
		game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] = '0';
	else if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] == '0')
	{
		i = 0;
		while(i < game->nb_d * 2)
		{
			if ((int)floorf(tmpy) == game->d_pos[i] && (int)floorf(tmpx) == game->d_pos[i + 1])
			{
				game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] = 'D';
				break;
			}
			i += 2;
		}
	}
}

void hooks(void *ptr)
{
	t_cub *game = (t_cub *)ptr;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		key_up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		key_down(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		key_A(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		key_D(game);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_cub *game = (t_cub *)param;
	if(keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		// open_door(game);		
		// ray_cast(game);
		put_minimap(game);
	}
}
