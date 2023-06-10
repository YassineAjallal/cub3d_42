#include "MLX42/include/MLX42/MLX42.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TILE_SIZE 32
#define PI M_PI
#define FOV_ANGLE (60 * (PI / 180))
#define NUM_RAYS 640
#define height 540
#define ray_inc (FOV_ANGLE / NUM_RAYS)
#define half_fov (FOV_ANGLE / 2)
#define scale 1

int test = 0;


float player_angel = (PI/2);
float p_x;
float p_y;

int h_index = 0;

char r_map[20][10] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', 'E', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

typedef struct t_cub
{
	mlx_t *mlx;
	mlx_image_t *map;
	mlx_image_t *player;
	mlx_texture_t *wallN;
	mlx_texture_t *wallS;
	mlx_texture_t *wallW;
	mlx_texture_t *wallE;
	xpm_t *xpm_w;
} s_cub;

s_cub cub;

int color_arrayN[(512 * 512)];
int color_arrayS[(512 * 512)];
int color_arrayE[(512 * 512)];
int color_arrayW[(512 * 512)];

float distances[NUM_RAYS];
int rgba(int r, int g, int b, float t)
{
	int hex = (r << 24) | (g << 16) | (b << 8) | (int)(t * 255);
	return hex;
}
void parseImage(mlx_texture_t *img, int arr[512 * 512])
{
	int i = 0;
	int j = 0;
	while (i < (img->width * img->height1) * img->bytes_per_pixel)
	{
		arr[j] = rgba(img->pixels[i], img->pixels[i + 1], img->pixels[i + 2], 1);
		j++;
		i += img->bytes_per_pixel;
	}
}
int ft_s(int s0, int s1)
{
	if (s0 < s1)
		return (1);
	return (-1);
}

void drawline(int x0, int y0, int x1, int y1, unsigned int colore)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1)
    {
        if (x0 >= 0 && x0 < NUM_RAYS && y0 >= 0 && y0 < height)
            mlx_put_pixel(cub.map, x0, y0, colore);
        int err2 = 2 * err;
        if (err2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_Texture(int x, int wall_height, int textPosX, int arr[512 * 512])
{
	float yIncr = (float)wall_height * 2 / (float)cub.wallN->height1;
	float y = (float)(height / 2 - wall_height);
	int i = 0;

	while (i < cub.wallN->height1)
	{
		drawline(x, (int)y, x, (int)(y + yIncr), arr[textPosX + (i * cub.wallN->height1)]);
		y += yIncr;
		i++;
	}
}

void check_player_view(int count, float ray_x, float ray_y, int wall_height, int textposX)
{
    if (ray_y < p_y)
        draw_Texture(count, wall_height, textposX, color_arrayN);
    else if (ray_y > p_y)
        draw_Texture(count, wall_height, textposX, color_arrayS);
    else if (ray_x > p_x)
        draw_Texture(count, wall_height, textposX, color_arrayE);
    else if (ray_x < p_x)
        draw_Texture(count, wall_height, textposX, color_arrayW);
}
void get_min_max(float *distances, float *min, float *max)
{
	*min = distances[0];
	*max = distances[0];
	int i = 0;
	while(i < NUM_RAYS)
	{
		if (distances[i] > *max)
			*max = distances[i];
		else if (distances[i] < *min)
			*min = distances[i];
		i++;
	}
	exit(0);
}

void ray_cast()
{
	float ray_angle;
	float count;
	float ray_x;
	float ray_y;
	float raycos;
	float raysin;
	char wall;

	ray_angle = player_angel - half_fov;
	count = 0;
	while (count < NUM_RAYS)
	{
		ray_x = (float)p_x;
		ray_y = (float)p_y;
		raycos = cos(ray_angle) / 64;
		raysin = sin(ray_angle) / 64;
		wall = '0';

		while (wall == '0'  || wall == 'N' || wall == 'S' || wall == 'E' || wall == 'W')
		{
			ray_x += raycos;
			ray_y += raysin;
			wall = r_map[(int)floorf(ray_y)][(int)floorf(ray_x)];
		}

		int hitIndexX = (int)floorf(ray_x / 512);
		int hitIndexY = (int)floorf(ray_y / 512);

		float prev_x = ray_x - raycos;
		float prev_y = ray_y - raysin;
		float delta_x = ray_x - prev_x;
		float delta_y = ray_y - prev_y;

		float distance = sqrtf((ray_x - p_x) * (ray_x - p_x) + (ray_y - p_y) * (ray_y - p_y));
		distance = distance * cos(ray_angle - player_angel);
		int wall_height = (int)floorf(((height / 2) / distance));
		float wallWidth = cub.wallN->width;
		float posXFloat = wallWidth * (ray_x + ray_y);
		int textposX = (int)posXFloat % cub.wallN->width;

		drawline(count, 0, count, (height / 2) - wall_height, rgba(80, 130, 200, 1));
		if((int)floorf(ray_y) == 0)
			draw_Texture(count, wall_height, textposX, color_arrayN);
		else if ((int)floorf(ray_y) == 19)
			draw_Texture(count, wall_height, textposX, color_arrayS);
		else if((int)floorf(ray_x) == 0)
			draw_Texture(count, wall_height, textposX, color_arrayE);
		else if((int)floorf(ray_x) == 9)
			draw_Texture(count, wall_height, textposX, color_arrayW);
		else
		{
			if (fabs(delta_x) > fabs(delta_y)) 
			{
				int side = 0;
				if (delta_x > 0) 
				{
					side = 1;
				}
				if (side == 0)
				{
					if (delta_x < 0) 
					{
						draw_Texture(count, wall_height, textposX, color_arrayE);
					}
					else 
					{
						draw_Texture(count, wall_height, textposX, color_arrayW);
					}
				}
				else
				{
					if (delta_x < 0) 
					{
						draw_Texture(count, wall_height, textposX, color_arrayW);
					}
					else 
					{
						draw_Texture(count, wall_height, textposX, color_arrayE);
					}
				}
			} 
			else 
			{
				int side = 2;
				if (delta_y > 0) 
				{
					side = 3;
				}
				if (side == 2)
				{
					if (delta_y < 0) 
					{
						draw_Texture(count, wall_height, textposX, color_arrayN);
					}
					else 
					{
						draw_Texture(count, wall_height, textposX, color_arrayS);
					}
				}
				else 
				{
					if (delta_y < 0) 
					{
						draw_Texture(count, wall_height, textposX, color_arrayS);
					}
					else 
					{
						draw_Texture(count, wall_height, textposX, color_arrayN);
					}
				}
			}
			
		}
		drawline(count, (height / 2) + wall_height, count, height, rgba(98, 105, 109, 1));
		ray_angle += ray_inc;
		count++;
	}
}

void hooks()
{

	if (mlx_is_key_down(cub.mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(cub.mlx, MLX_KEY_UP))
	{
		float playercos = cos(player_angel) * 0.1;
		float playersin = sin(player_angel) * 0.1;
		float tmpx = p_x + playercos;
		float tmpy = p_y + playersin;
		if (r_map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
		{
			p_y = tmpy;
			p_x = tmpx;

		}
	}
	if (mlx_is_key_down(cub.mlx, MLX_KEY_DOWN))
	{
		float playercos = cos(player_angel) * 0.1;
		float playersin = sin(player_angel) * 0.1;
		float tmpx = p_x - playercos;
		float tmpy = p_y - playersin;
		if (r_map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
		{
			p_y = tmpy;
			p_x = tmpx;
		}
	}
	if (mlx_is_key_down(cub.mlx, MLX_KEY_A))
	{
		player_angel -= 0.05;
		if (player_angel < 0)
			player_angel += 2 * M_PI;
		else if (player_angel > 2 * M_PI)
			player_angel -= 2 * M_PI;
	}
	if (mlx_is_key_down(cub.mlx, MLX_KEY_D))
	{
		player_angel += 0.05;
		if (player_angel < 0)
			player_angel += 2 * M_PI;
		else if (player_angel > 2 * M_PI)
			player_angel -= 2 * M_PI;
	}
	ray_cast();
}


void find_player()
{
	int i = 0;
	int j;

	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (r_map[i][j] == 'N' || r_map[i][j] == 'S' || r_map[i][j] == 'E' || r_map[i][j] == 'W')
			{
				p_x = j;
				p_y = i;
				if(r_map[i][j] == 'N')
					player_angel = 3 * PI / 2;
				if(r_map[i][j] == 'S')
					player_angel = PI / 2;
				if(r_map[i][j] == 'E')
					player_angel = 0;
				if(r_map[i][j] == 'W')
					player_angel = PI;
				return;
			}
			j++;
		}
		i++;
	}
}

int main()
{
	cub.mlx = mlx_init(NUM_RAYS, height, "CUB3D", 0);
	cub.wallN = mlx_load_png("images/photo-pngrepo-com.png");
	cub.wallS = mlx_load_png("images/1.png");
	cub.wallW = mlx_load_png("images/brick-wall-wall-pngrepo-com.png");
	cub.wallE = mlx_load_png("images/magnifying-glass-pngrepo-com.png");

	cub.map = mlx_new_image(cub.mlx, NUM_RAYS, height);
	mlx_image_to_window(cub.mlx, cub.map, 0, 0);
	parseImage(cub.wallN, color_arrayN);
	parseImage(cub.wallS, color_arrayS);
	parseImage(cub.wallW, color_arrayW);
	parseImage(cub.wallE, color_arrayE);


	find_player();
	ray_cast();
	mlx_loop_hook(cub.mlx, hooks, NULL);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	return (0);
}