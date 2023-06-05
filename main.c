#include "/Users/mkhairou/MLX42/include/MLX42/MLX42.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TILE_SIZE 32;
#define PI 3.1415926535
#define FOV_ANGLE (60 * (PI / 180))
#define NUM_RAYS 640
#define height 540
#define ray_inc (FOV_ANGLE / NUM_RAYS)
#define half_fov (FOV_ANGLE / 2)

float player_angel = (90 * (PI/180));
float	p_x;
float	p_y;

int h_index = 0;

char r_map[10][10]= {
	{'1', '1', '1', '1','1','1','1','1','1', '1'},
	{'1', '0', '0', '0','0','0','0','0','0', '1'},
	{'1', '0', '0', '0','0','0','0','0','0', '1'},
	{'1', '0', '0', '0','0','0','0','0','0', '1'},
	{'1', '0', '0', '0','0','0','0','0','0', '1'},
	{'1', '0', '0', '0','0','0','0','0','0', '1'},
	{'1', '0', '0', '0','0','0','0','0','0', '1'},
	{'1', '0', 'p', '0','0','0','0','0','0', '1'},
	{'1', '0', '0', '0','0','0','0','0','0', '1'},
	{'1', '1', '1', '1','1','1','1','1','1', '1'}
};
typedef struct t_cub{
	mlx_t 		*mlx;
	mlx_image_t *map;
	mlx_image_t *player;
	mlx_texture_t *wall;
	xpm_t *xpm_w;
}s_cub;

s_cub cub;

void drawline(double X0, double Y0, double X1, double Y1, unsigned int colore)
{
    double dx = X1 - X0;
    double dy = Y1 - Y0;

    int steps = (int)(fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy));

    double Xinc = dx / (double)steps;
    double Yinc = dy / (double)steps;

    double X = X0;
    double Y = Y0;

    for (int i = 0; i <= steps; i++)
	{
        int x = (int)round(X);
        int y = (int)round(Y);

        if (x >= 0 && x < NUM_RAYS && y >= 0 && y < height) {
            mlx_put_pixel(cub.map, x, y, colore);
        }

        X += Xinc;
        Y += Yinc;
    }
}
int	rgba(int r, int g, int b, float t)
{
	int hex = (r << 24) | (g << 16) | (b << 8) | (int)(t * 255);
    return hex;
}

void drawline1(double X0, double Y0, double X1, double Y1, unsigned int colore)
{
    double dx = X1 - X0;
    double dy = Y1 - Y0;

    int steps = (int)(fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy));

    double Xinc = dx / (double)steps;
    double Yinc = dy / (double)steps;

    double X = X0;
    double Y = Y0;

    for (int i = 0; i <= steps; i++)
	{
        int x = (int)round(X);
        int y = (int)round(Y);

        if (x >= 0 && x < NUM_RAYS && y >= 0 && y < height) {
            mlx_put_pixel(cub.map, x, y, cub.wall->pixels[h_index]);
			h_index++;
        }
        X += Xinc;
        Y += Yinc;
    }
}

void ray_cast()
{
	float ray_angle;
	float count;
	float ray_x;
	float ray_y;
	float raycos;
	float raysin;
	char	wall;

	ray_angle = player_angel - half_fov;
	count = 0;
	while (count < NUM_RAYS)
	{
		ray_x = (float)p_x;
		ray_y = (float)p_y;
		raycos = cos(ray_angle) / 64;
		raysin = sin(ray_angle) / 64;
		wall = '0';
		while (wall == '0' || wall == 'p')
		{
			ray_x += raycos;
			ray_y += raysin;
			wall = r_map[(int)floorf(ray_y)][(int)floorf(ray_x)];
		}
		float distance = sqrtf((ray_x - p_x) * (ray_x - p_x) + (ray_y - p_y) * (ray_y - p_y));
		distance = distance * cos(ray_angle - player_angel);
		float wall_height =  floorf(((height / 2) / distance));
		drawline(count,0,count,(height / 2)- wall_height, rgba(80, 130, 200,1));
		drawline1(count,(height / 2)- wall_height, count, (height / 2) + wall_height, rgba(0, 86, 145,1));
		if(h_index >= 64 *64)
			h_index = 0;
		drawline(count, (height / 2)+ wall_height, count, height,rgba(98, 105, 109,1));
		ray_angle += ray_inc;
		count++;
	}
}

void	hooks()
{

	if(mlx_is_key_down(cub.mlx,MLX_KEY_ESCAPE))
		exit(0);
	if(mlx_is_key_down(cub.mlx,MLX_KEY_UP))
	{
		float playercos = cos(player_angel) * 0.5;
		float playersin = sin(player_angel) * 0.5;
		float tmpx = p_x + playercos;
		float tmpy = p_y + playersin;
		if(r_map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
		{
			p_y = tmpy;
			p_x = tmpx;
		}
		ray_cast();
	}
	if(mlx_is_key_down(cub.mlx,MLX_KEY_DOWN))
	{
		float playercos = cos(player_angel) * 0.5;
		float playersin = sin(player_angel) * 0.5;
		float tmpx = p_x - playercos;
		float tmpy = p_y - playersin;
		if(r_map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
		{
			p_y = tmpy;
			p_x = tmpx;
		}
		ray_cast();
	}
	if(mlx_is_key_down(cub.mlx,MLX_KEY_LEFT))
	{
		player_angel -= 0.1;
		ray_cast();
	}
	if(mlx_is_key_down(cub.mlx,MLX_KEY_RIGHT))
	{
		player_angel += 0.1;
		ray_cast();
	}

}

// void drw_player()
// {
// 	int radius = 15;
//     int centerX = 15;
//     int centerY = 15;
// 	int y;
// 	int x;

// 	y = -radius;
//     while (y <= radius)
//     {
// 		x = -radius;
//         while ( x <= radius)
//         {
//             if (x * x + y * y <= radius * radius)
//             {
//                 int pixelX = centerX + x;
//                 int pixelY = centerY + y;
//                 mlx_put_pixel(cub.player, pixelX, pixelY, 0xFFFFFF);
//             }
// 			x++;
//         }
// 		y++;
//     }
// }


// void	drw_all()
// {
// 	int i = 0;
// 	int j;

// 	while (i < 5)
// 	{
// 		j = 0;
// 		while (j < 5)
// 		{
// 			if (r_map[i][j] == '1')
// 				mlx_put_pixel(cub.map, j * 32, i * 32, 0xFFFFFF);
// 			if(r_map[i][j] == '0')
// 				mlx_put_pixel(cub.map, j * 32, i * 32, 0x000000);
// 			// if(r_map[i][j] == 'p')
// 			// 	drw_player();
// 			j++;
// 		}
// 		i++;
// 	}

// }
void	drw_pixels()
{
	// drw_all();)
	ray_cast();
}

void	find_player()
{
	int i = 0;
	int j;

	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (r_map[i][j] == 'p')
			{
				p_x = j;
				p_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

int main()
{
	cub.mlx = mlx_init(NUM_RAYS,height,"CUB3D",0);
	cub.wall = mlx_load_png("./BRICK_3B.png");
	cub.map = mlx_new_image(cub.mlx,NUM_RAYS,height);
	cub.player = mlx_new_image(cub.mlx,50,50);
	mlx_image_to_window(cub.mlx, cub.map, 0,0);
	mlx_image_to_window(cub.mlx, cub.player, (NUM_RAYS / 2), (height / 2));
	// mlx_loop_hook(cub.mlx,drw_pixels,NULL);
	int	i = 0;
		// printf("%d\n",cub.wall->height1);
		// printf("%d\n",cub.wall->width);
	// while (i < cub.wall->height1)
	// {

	// 	printf("%c\n",cub.wall->pixels[i]);
	// 	i++;
	// }

	find_player();
	ray_cast();
	mlx_loop_hook(cub.mlx,hooks,NULL);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	return(0);
}

