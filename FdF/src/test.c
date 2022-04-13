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

int	render_line(t_img *img, t_coord start, t_coord end)
{
	int	a;
	int	b;
	int d_a;
	int	d_b;
	int p;
	int	color;
	int ender;

	if ((end.x - start.x) > (end.y - start.y))
	{
		a = start.x;
		b = start.y;
		d_a = ft_abs(end.x - start.x);
		d_b = ft_abs(end.y - start.y);
		ender = end.x;
	}
	else
	{
		a = start.y;
		b = start.x;
		d_b = end.x - start.x;
		d_a = end.y - start.y;
		ender = end.y;
	}
	color = RED_PIXEL;
	if (start.height > 5)
		color = GREEN_PIXEL;

	p = 2 * d_b - d_a;
	while (a <= ender)
	{
		if (ender == end.x)
			img_pix_put(img, a, b, color);
		else
			img_pix_put(img, b, a, color);
		a++;
		if ( p < 0)
		{
			p = p + 2 * d_b;
		}
		else
		{
			p = p + 2 * d_b - 2 * d_a;
			b++;
		}
	}
	img_pix_put(img, end.x, end.y, color);
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

