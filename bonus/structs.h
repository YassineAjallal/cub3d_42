/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:38:28 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/30 11:42:19 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#include "/Users/mkhairou/MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#define TILE 32
#define FOV_ANGLE (60 * (M_PI / 180))
#define WIDTH 1180
#define NUM_RAYS WIDTH

#define HEIGHT 560
#define ray_inc (FOV_ANGLE / WIDTH)
#define half_fov (FOV_ANGLE / 2)

typedef enum e_side {
	NO,
	SO,
	WE,
	EA,
	DO
} t_side;

typedef struct s_map
{
	char *line;
	char cnofig;
	struct s_map *next;

} t_map;

typedef struct s_coord
{
	float x;
	float y;
} t_coord;

typedef struct s_textures
{
	int *color_arrayN;
	int *color_arrayS;
	int *color_arrayE;
	int *color_arrayW;
	int *color_arrayD;
} t_textures;


typedef struct s_cub
{
	char **map;
	float player_angle;
	int ciel_color;
	int floor_color;
	char **textures_img;
	t_coord p_coord;
	t_textures *textures;
	mlx_t *mlx;
	mlx_image_t *map_img;
	mlx_image_t *minimap_img;
	mlx_texture_t *wallN;
	mlx_texture_t *wallS;
	mlx_texture_t *wallW;
	mlx_texture_t *wallE;
	mlx_texture_t *dooR;
	mlx_texture_t *sprite[3];
	int *d_pos;
	int nb_d;
	int index;
	int mouse_x;
	int mouse_y;
} t_cub;

int rgba(int r, int g, int b, float t);
#endif
