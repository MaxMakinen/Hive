/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barnsley_fern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:08:19 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/26 10:40:30 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_point	next_point(double x, double y, double random)
{
	t_point	temp;

	if (random < 0.01)
	{
		temp.x = 0;
		temp.y = 0.16 * y;
	}
	else if (random < 0.86)
	{
		temp.x = 0.85 * x + 0.04 * y;
		temp.y = -0.04 * x + 0.85 * y + 1.6;
	}
	else if (random < 0.93)
	{
		temp.x = 0.20 * x + -0.26 * y;
		temp.y = 0.23 * x + 0.22 * y + 1.6;
	}
	else
	{
		temp.x = -0.15 * x + 0.28 * y;
		temp.y = 0.26 * x + 0.24 * y + 0.44;
	}
	return (temp);
}

void	draw_point(double x, double y, t_win *win, double random)
{
	double	px;
	double	py;

	px = ft_linear_conversion(win->x_range, win->width_range, \
		(x + win->x_offset));
	py = ft_linear_conversion(win->y_range, ft_create_range(HEIGHT, 0), \
		(y + win->y_offset));
	img_pixel_put(random, px, py, win);
}

void	barnsley_fern(t_win *win)
{
	int		i;
	t_point	coords;
	double	random;
	int		n;

	coords.x = 0;
	coords.y = 0;
	win->col_finish = hex_to_rgb(0x00D9FF);
	i = 0;
	while (i < win->max_iter)
	{
		random = (double)rand() / RAND_MAX;
		n = rand() % (25 - 1 + 1) + 1;
		draw_point(coords.x, coords.y, win, n);
		coords = next_point(coords.x, coords.y, random);
		i++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}
