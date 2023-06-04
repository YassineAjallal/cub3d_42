#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../MLX42/include/MLX42/MLX42.h"

#define PI 3.1415926535

float pa,pdx,pdy;
#define FOV_ANGLE (60 * (PI / 180))

int x = 50;
int y = 100;
int view = 200;
mlx_image_t *wall;
mlx_t *ptr;
void *win;
void *img;
mlx_image_t *pxl;
mlx_image_t *ray;
mlx_texture_t *imgj;
char map[5][5] = {
	{'1','p','1','1','1'},
	{'1','0','0','0','1'},
	{'1','0','1','0','1'},
	{'1','p','0','0','1'},
	{'1','1','1','1','1'}
};

int ft_s(int s0, int s1)
{
	if (s0 < s1)
		return (1);
	return (-1);
}

void my_line1(int x0, int y0, int x1, int y1, void *mlx, void *win, int color)
{
	int dx;
	int dy;
	int err;
	int e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if (dx > dy)
		err = dx / 2;
	else
		err = -dy / 2;
	mlx_image_t *px;
	while (1)
	{
		if ( x0== x1 && y0 == y1)
			break;
		px = mlx_new_image(ptr, 1, 1);
		mlx_image_to_window(ptr, px, x0, y0);
		if (map[y0 / 40][x0 / 40] == '1')
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += ft_s(x0, x1);
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += ft_s(y0, y1);
		}
	}

}

void my_line(int x0, int y0, int x1, int y1, void *mlx, void *win, int color)
{
	int dx;
	int dy;
	int px = 0;
	int new_x = 0;
	int err;
	int e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if (dx > dy)
		err = dx / 2;
	else
		err = -dy / 2;
	while (1)
	{
		// if (map[y0 / 40][x0 / 40] == '1')
		// 	break;
		if ( x0== x1 && y0 == y1)
			break;
		ray = mlx_new_image(ptr, 1, 1);
		// mlx_put_pixel(ray,x0, y0, 0xffffff);
		mlx_image_to_window(ptr, ray, x0, y0);
		new_x++;
		if (new_x - px == 10)
		{
			px = new_x;
			my_line1(x, y , x0, y0, ptr, win, 0xffffff);
		}
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += ft_s(x0, x1);
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += ft_s(y0, y1);
		}
	}

}

void draw_fov()
{
    float angle = pa - FOV_ANGLE / 2;
    float end_angle = pa + FOV_ANGLE / 2;
	int target_x;
	int target_y;
	int target_x1 = x + cos(angle) * view;
    int target_y1 = y + sin(angle) * view;
	int target_x2 = x + cos(end_angle) * view;
    int target_y2 = y + sin(end_angle) * view;
	my_line(target_x1, target_y1, target_x2, target_y2, ptr, win, 0xFFFFFF);
	my_line(x, y, target_x1, target_y1, ptr, win, 0xFFFFFF);
	my_line(x, y, target_x2, target_y2, ptr, win, 0xFFFFFF);
    // while (angle <= end_angle)
    // {
	// 	target_x = x + cos(angle) * view;
    //     target_y = y + sin(angle) * view;
	// 	my_line(x, y, target_x, target_y, ptr, win, 0xFFFFFF);
    //     angle += 0.01;
    // }
	// angle = pa - FOV_ANGLE / 2;
    // end_angle = pa + FOV_ANGLE / 2;
	// int target_x1 = x + cos(angle) * view;
    // int target_y1 = y + sin(angle) * view;
	// int target_x2 = x + cos(end_angle) * view;
    // int target_y2 = y + sin(end_angle) * view;

	my_line(target_x1, target_y1, target_x2, target_y2, ptr, win, 0xFFFFFF);
}

mlx_keyfunc	key_hook(struct mlx_key_data keycode, void *param)
{
	int oldx;
	int oldy;

	oldx = x;
	oldy = y;
	mlx_is_key_down(ptr, 263);
	if (mlx_is_key_down( ptr,MLX_KEY_A))
	{
		pa -= 0.1;
		if(pa < 0)
			pa = 2 * PI;
		pdx = cos(pa);
		pdy = sin(pa);
	}
	if (mlx_is_key_down( ptr,MLX_KEY_D))
	{
		pa += 0.1;
		if(pa > 2 * PI)
			pa = 0;
		pdx = cos(pa);
		pdy = sin(pa);
	}
	if (mlx_is_key_down( ptr,MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down( ptr, MLX_KEY_LEFT) && map[y / 40][(x - (int)floorf(pdx)) / 40] != '1')
	{
		printf("left\n");
		x -= pdx;
		y -= pdy;
	}
	if (mlx_is_key_down( ptr,MLX_KEY_RIGHT) && map[y / 40][(x + (int)floorf(pdx)) / 40] != '1')
	{
		printf("right\n");
		x += pdx;
		y += pdy;
	}
	if (mlx_is_key_down( ptr, MLX_KEY_DOWN) && map[(y + (int)floorf(pdy)) / 40][x / 40] != '1')
	{
		printf("down\n");
		x += pdx;
		y += pdy;
	}
	if (mlx_is_key_down( ptr, MLX_KEY_UP) && map[(y - (int)floorf(pdy)) / 40][x / 40] != '1')
	{
		printf("up\n");
		x -= pdx;
		y -= pdy;
	}
	// }
	// int i = 0;
	// int j = 0;
	// // mlx_put_image_to_window(ptr, win, img, x, y);
	// while (i < 5)
	// {
	// 	j = 0;
	// 	while (j < 5)
	// 	{
	// 		wall = mlx_texture_to_image(ptr, imgj);
	// 		if (map[i][j] == '1')
	// 		{
	// 			mlx_image_to_window(ptr, wall, i * wall->width, j * wall->height);
	// 		}
	// 		if (map[i][j] == 'p')
	// 		{
	// 			pxl = mlx_new_image(ptr, 50, 50);
	// 			mlx_put_pixel(pxl,x * pxl->width, pxl->width, 0x1f1f1f);
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	// if(oldx != x || oldy != y)
	// 	draw_fov();
}

int main(int argc, char const *argv[])
{
	ptr = mlx_init(1280,720, "Hello World",0);
	if(!ptr)
	{
		printf("Error\n");
	}
	int width = 32;
	const char a[]= "./wall.xpm";
	// win = mlx_new_window(ptr, 1280, 720, "Hello World");
	imgj = mlx_load_png("../Shoot.png");
	if(!imgj)
	{
		printf("%d\n",mlx_errno);
	}
	// if (!imgj)
	// {
	// 	return (0);
	// }
	// wall = mlx_new_image(ptr, 40,40);
	// wall = mlx_texture_to_image(ptr, imgj);
	xpm_t* xpm = mlx_load_xpm42("../AnyConv.com__Shoot.xpm42");
	if (!xpm)
		printf("%s\n",mlx_strerror(mlx_errno));
	// 	error();
	// pxl = mlx_new_image(ptr, 1, 1);
	// img = mlx_xpm_file_to_image(ptr, "./wall.xpm", &width, &width);
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	int i = 0;
	int j = 0;
	// mlx_put_image_to_window(ptr, win, img, x, y);
	mlx_image_t* wall = mlx_texture_to_image(ptr, &xpm->texture);
	// pxl = mlx_new_image(ptr, 50, 50);
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			// if (map[i][j] == '1')
			// {
				mlx_image_to_window(ptr, wall, j * wall->width, i * wall->height);
			// }
			// if (map[i][j] == 'p')
			// {
				// x = j * 40;
				// y = i * 40;
				// mlx_put_pixel(pxl,x, y, 0xffffff);
				// mlx_image_to_window(ptr, pxl, x, y);
			// }
			j++;
		}
		i++;
	}
	// mlx_pixel_put(ptr, win, x, y, 0xFFFFFF);
	mlx_key_hook(ptr, (mlx_keyfunc)key_hook, NULL);
	mlx_loop(ptr);
	return 0;
}
