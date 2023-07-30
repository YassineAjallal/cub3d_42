/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:04:14 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/30 16:20:00 by yajallal         ###   ########.fr       */
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
void my_keyhook(mlx_key_data_t keydata, void* param);

int init_game(t_cub *game);
void find_player(t_cub *game);

void	draw_rays(t_cub *game);
void	draw_wall(int h, int w, t_cub *game, int color);
void	draw_maps(t_cub *game);
void	put_minimap(t_cub *game);
void	drawline_mini(t_coord c0, t_coord c1, t_cub *game, int color);

void draw_Texture(int x, int wall_height, int textPosX, t_cub *game, int *arr, mlx_texture_t *img);
void setup_textures(t_cub *game, float ray_x, float ray_y, float raycos, float raysin, int count, float wall_height);
void ray_cast(t_cub *game);

void parseImage(mlx_texture_t *img, int *arr);

void rays(t_cub *game);
float normlize_angle(float angle);

double calc_dis(t_cub *game, t_coord hit, t_coord p);
t_coord vertical_inter(t_cub *game, double angle, t_coord p);
t_coord horizontal_inter(t_cub *game, double angle, t_coord p);

void rays_minimap(t_cub *game);
#endif
