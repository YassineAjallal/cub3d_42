/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:04:14 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/12 12:01:30 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "../parsing/parsing.h"
#include "../structs.h"


void drawline(t_coord c0, t_coord c1, t_cub *game, int color);

void key_up(t_cub *game);
void key_down(t_cub *game);
void key_A(t_cub *game);
void key_D(t_cub *game);
void hooks(void *ptr);

void init_game(t_cub *game);
int rgba(int r, int g, int b, float t);
void find_player(t_cub *game);

// void draw_rays(t_cub *game);
// void	drw_wall(int h, int w, t_cub *game);
// void	draw_maps(t_cub *game);
// void drw_pixels(t_cub *game);

void draw_Texture(int x, int wall_height, int textPosX, t_cub *game, int arr[512 * 512]);
void setup_textures(t_cub *game, float ray_x, float ray_y, float raycos, float raysin, int count, float wall_height);
void ray_cast(t_cub *game);

#endif
