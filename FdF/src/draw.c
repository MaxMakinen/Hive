/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:38:41 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/23 11:30:03 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	render_line(t_img *img, t_vector start, t_vector end)
{
	int	x;
	int	y;
	float	m;
	int delta;
	int	adjust;
	int	offset;
	int	threshold;
	int	threshold_inc;
	t_vector dist;

	float meep;

	dist.x = start.x - end.x;
	dist.y = start.y - end.y;
	if (dist.x == 0)
	{
		if (end.y < start.y)
		{
			meep = start.y;
			start.y = end.y;
			end.y = meep;
		}
		while (start.y <= end.y)
			img_pix_put(img, start.x, start.y++, check_color(start));
	}
	else
	{
		m = (float)dist.y / dist.x;
		offset = 0;
		adjust = 1;
		if (m < 0)
			adjust = -1;
		if (m <= 1 && m >= -1)
		{
			delta = ft_abs(dist.y) * 2;
			threshold = ft_abs(dist.x);
			threshold_inc = ft_abs(dist.x) * 2;
			y = start.y;
			if (end.x < start.x)
			{
				meep = start.x;
				start.x = end.x;
				end.x = meep;
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
			delta= ft_abs(dist.x) * 2;
			threshold = ft_abs(dist.y);
			threshold_inc = ft_abs(dist.y) * 2;
			x = start.x;
			if (end.y < start.y)
			{
				meep = start.y;
				start.y = end.y;
				end.y = meep;
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
//				render_line(&data->img, data->map.vec[y][x], data->map.vec[y][x + 1]);
				render_line(&data->img, data->map.coords[y][x].vect, data->map.coords[y][x + 1].vect);
			if((y + 1) < data->map.y_max)
//				render_line(&data->img, data->map.vec[y][x], data->map.vec[y + 1][x]);
				render_line(&data->img, data->map.coords[y][x].vect, data->map.coords[y + 1][x].vect);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

void img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	float	temp;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

		/* img versions */

void render_background(t_img *img, int color)
{
	int	i;
	int	j;
	int x, xa, ya;
	int	y, xb, yb;

	x = WINDOW_HEIGHT / 10;
	y = WINDOW_WIDTH / 10;
	xa = x;
	ya = y;
	xb = 4 * x;
	yb = 4 * y;
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img , j, i, color);
			/*
			if (j == WINDOW_WIDTH / 2)
				img_pix_put(img , j, i, WHITE_PIXEL);
			else if (i == WINDOW_HEIGHT / 2)
				img_pix_put(img , j, i, WHITE_PIXEL);
			if (i == x && j > yb && j < (yb + ya + ya))
				img_pix_put(img , j, i, WHITE_PIXEL);
			if (i > x)
				x += xa;
			*/
			j++;
		}
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

int	check_color(t_vector coord)
{
	if (coord.z > 0.995f)
		return (GREEN_PIXEL);
	return (RED_PIXEL);
}

