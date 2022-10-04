/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_initialise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:36:08 by deelliot          #+#    #+#             */
/*   Updated: 2022/09/07 10:57:50 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	initialise_colour(t_win *win)
{
	if (win->colour == 0)
		win->col_start = hex_to_rgb(0x0F0406);
	if (win->colour == 1)
		win->col_start = hex_to_rgb(0x060F04);
	if (win->colour == 2)
		win->col_start = hex_to_rgb(0x04060F);
	if (win->colour == 3)
		win->col_start = hex_to_rgb(0x00D9FF);
	if (win->colour == 4)
		win->col_start = hex_to_rgb(0xBDEB0A);
}

void	initialise_image(t_img *img, t_win *win)
{
	img->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	if (!img->img)
		handle_errors(win);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->length, \
	&img->endian);
	if (!img->addr)
		handle_errors(win);
}

void	initialise_window(t_win *win, char *str)
{
	win->mlx = mlx_init();
	if (!win->mlx)
		handle_errors(win);
	win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, str);
	if (!win->win)
		handle_errors(win);
	win->zoom = 0.0;
	win->max_iter = 100;
	win->x_offset = 0.0;
	win->y_offset = 0.0;
	win->colour = 0;
	win->width_range = ft_create_range(0, WIDTH);
	win->height_range = ft_create_range(0, HEIGHT);
	win->mouse_x = -0.7269;
	win->mouse_y = 0.1889;
	win->lock = 1;
	win->power = 3;
	fractal_positions(win);
}

/* positions fractal to centre of window and sets iterations*/

static void	positions_continued(t_win *win)
{
	if (win->fractol_option == 4)
	{
		win->x_offset = -40;
		win->y_offset = 0;
		win->x_range = ft_create_range(-3.47, 3.47);
		win->y_range = ft_create_range(-2.32, 2.32);
	}
	else if (win->fractol_option == 5)
	{
		win->x_offset = -120;
		win->y_offset = -100;
		win->x_range = ft_create_range(-2.48, 2.48);
		win->y_range = ft_create_range(-1.63, 1.63);
	}
	else if (win->fractol_option == 6)
	{
		win->x_offset = 0;
		win->y_offset = 0;
		win->x_range = ft_create_range(-2.182, 2.6558);
		win->y_range = ft_create_range(0, 9.9983);
		win->max_iter = 1000000;
	}
}

void	fractal_positions(t_win *win)
{
	if (win->fractol_option == 0)
	{
		win->x_offset = 0;
		win->y_offset = 0;
		win->x_range = ft_create_range(-2, 2);
		win->y_range = ft_create_range(-1.25, 1.25);
		win->max_iter = 300;
	}
	else if (win->fractol_option == 1)
	{
		win->x_offset = -180;
		win->y_offset = 0;
		win->x_range = ft_create_range(-2.40, 2.40);
		win->y_range = ft_create_range(-1.58, 1.58);
		win->max_iter = 100;
	}
	else if ((win->fractol_option == 2) || (win->fractol_option == 3))
	{
		win->x_offset = -30;
		win->y_offset = 10;
		win->x_range = ft_create_range(-3.47, 3.47);
		win->y_range = ft_create_range(-2.32, 2.32);
	}
	else
		positions_continued(win);
}
