/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:43 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/13 18:05:57 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "fdf.h"
#include "libft.h"

#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>

#define MLX_ERROR 1

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define BLUE_PIXEL 0xFF
#define WHITE_PIXEL 0xFFFFFF
#define BLACK_PIXEL 0x000000

int	ft_abs(int num)
{
	if (num < 0)
		num = -num;
	return (num);
}

int handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}

	printf("Keypress: %d\n", keysym);
	return (0);
}
/*
int handle_keyrelease(int keysym, t_data *data)
{
	printf("Keyrelease: %d\n", keysym);
	return (0);
}
*/

void img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len +x * (img->bpp / 8));
	*(int *)pixel = color;
}

		/* img versions */

void render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(img , j++, i, color);
		i++;
	}
}

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
		while (i < rect.y + rect.height)
		{
			j = rect.x;
			while (j < rect.x + rect.width)
				img_pix_put(img, j++, i, rect.color);
			i++;
		}
		return (0);
}

t_coord matmul(t_coord)
{
	int		rows;
	int		cols;
	int		index;
	int		len;
	t_coord result;

	rows = 1;
	index = 1;
	len = 4;
	while (rows < len)
	{
		cols = 1;


}

t_coord	rotate_z(t_coord coord)
{
	{cos(angle), -sin(angle), 0}
	{sin(angle), cos(angle), 0}
	{0, 0, 1};
}

t_coord	rotate_x(t_coord coord)
{
	{1, 0, 0};
	{0, cos(angle), -sin(angle)}
	{0, sin(angle), cos(angle)}
}

t_coord	rotate_y(t_coord coord)
{
	{cos(angle), 0, sin(angle)};
	{0, 1, 0};
	{-sin(angle), 0, cos(angle)};
}

int	check_color(t_coord coord)
{
	if (coord.height > 0)
		return (GREEN_PIXEL);
	return (RED_PIXEL);
}

int	render_line(t_img *img, t_coord start, t_coord end)
{
	int	x;
	int	y;
	int	m;
	int	delta_x;
	int	delta_y;
	int delta;
	int	adjust;
	int	offset;
	int	threshold;
	int	threshold_inc;
	int color;

	delta_x = start.x - end.x;
	delta_y = start.y - end.y;
	color = RED_PIXEL;
	if (delta_x == 0)
	{
		if (end.y < start.y)
			ft_swapint(&start.y, &end.y);
		while (start.y <= end.y)
			img_pix_put(img, start.x, start.y++, check_color(start));
	}
	else
	{
		m = (float)delta_y / delta_x;
		offset = 0;
		adjust = 1;
		if (m < 0)
			adjust = -1;
		if (m <= 1 && m >= -1)
		{
			delta = ft_abs(delta_y) * 2;
			threshold = ft_abs(delta_x);
			threshold_inc = ft_abs(delta_x) * 2;
			y = start.y;
			if (end.x < start.x)
			{
				ft_swapint(&start.x, &end.x);
				y = end.y;
			}
			while (start.x <= end.x)
			{
				img_pix_put(img, start.x++, y, check_color(start));
				offset += delta;
				if (offset >= threshold)
				{
					y += adjust;
					threshold +=threshold_inc;
				}
			}
		}
		else
		{
			delta= ft_abs(delta_x) * 2;
			threshold = ft_abs(delta_y);
			threshold_inc = ft_abs(delta_y) * 2;
			x = start.x;
			if (end.y < start.y)
			{
				ft_swapint(&start.y, &end.y);
				x = end.x;
			}
			while (start.y < end.y)
			{
				img_pix_put(img, x, start.y++, check_color(start));
				offset += delta;
				if (offset >= threshold)
				{
					x += adjust;
					threshold += threshold_inc;
				}
			}
		}
	}
	return (0);
}

int render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, BLACK_PIXEL);
	while (y < data->map.y_max)
	{
		x = 0;
		while (x < data->map.x_max)
		{
			if((x + 1) < data->map.x_max)
				render_line(&data->img, data->map.coords[y][x], data->map.coords[y][x + 1]);
			if((y + 1) < data->map.y_max)
				render_line(&data->img, data->map.coords[y][x], data->map.coords[y + 1][x]);
			x++;
		}
		y++;
	}
	
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl("Usage: fdf <input file>");
		return(1);
	}
	data.map = input(argv[1], &data.map);

	data.mlx_ptr = mlx_init();
	/* Create the image */
	if (data.mlx_ptr == NULL)
		return(MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr)	;
		return (MLX_ERROR);
	}

	/* setup hooks */
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
//	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}

