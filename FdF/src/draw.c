/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:38:41 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/24 17:16:07 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float ft_pyth(float a, float b)
{
	return (sqrtf(powf(a, 2) + powf(b, 2)));
}

double ft_percent(int num, int min, int max)
{
	double diff;
	double range;

	diff = num - min;
	range = max - min;
	if (diff == 0)
		return (1.0);
	return (diff / range);
}

float ft_norm(float num, float min, float max)
{
	float	norm;

	if (min < 0)
	{
		num += min + 1;
		max += min + 1;
		min += min + 1;
	}
	norm = ((num - min) / (max - min));
	if (norm <= 0.0f)
		return (1.0f);
	return (norm);
}

float ft_lerp(float norm, float min, float max)
{
	return ((max-min) * norm + min);
}
int	render_line(t_img *img, t_coord start, t_coord end)
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
	float hypotenuse;

	float meep;

	dist.x = start.vect.x - end.vect.x;
	dist.y = start.vect.y - end.vect.y;
	dist.z = start.vect.z - end.vect.z;
	if (dist.x == 0)
	{
		if (end.vect.y < start.vect.y)
		{
			meep = start.vect.y;
			start.vect.y = end.vect.y;
			end.vect.y = meep;
		}
		while (start.vect.y <= end.vect.y)
			img_pix_put(img, start.vect.x, start.vect.y++, check_color((t_vector){x, y, 0}, start, end, dist));
	}
	else
	{
		m = dist.y / dist.x;
		offset = 0;
		adjust = 1;
		if (m < 0)
			adjust = -1;
		if (m <= 1 && m >= -1)
		{
			delta = ft_abs(dist.y) * 2;
			threshold = ft_abs(dist.x);
			threshold_inc = ft_abs(dist.x) * 2;
			y = start.vect.y;
			if (end.vect.x < start.vect.x)
			{
				meep = start.vect.x;
				start.vect.x = end.vect.x;
				end.vect.x = meep;
				y = end.vect.y;
			}
			while (start.vect.x <= end.vect.x)
			{
				img_pix_put(img, start.vect.x++, y, check_color((t_vector){x, y, 0}, start, end, dist));
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
			x = start.vect.x;
			if (end.vect.y < start.vect.y)
			{
				meep = start.vect.y;
				start.vect.y = end.vect.y;
				end.vect.y = meep;
				x = end.vect.x;
			}
			while (start.vect.y < end.vect.y)
			{
				img_pix_put(img, x, start.vect.y++, check_color((t_vector){x, y, 0}, start, end, dist));
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
	//project(&data->map, data->proj);
	while (y < data->map.y_max)
	{
		x = 0;
		while (x < data->map.x_max)
		{
			if((x + 1) < data->map.x_max)
//				render_line(&data->img, data->map.vec[y][x], data->map.vec[y][x + 1]);
				render_line(&data->img, data->map.vec[y][x], data->map.vec[y][x + 1]);
			if((y + 1) < data->map.y_max)
//				render_line(&data->img, data->map.vec[y][x], data->map.vec[y + 1][x]);
				render_line(&data->img, data->map.vec[y][x], data->map.vec[y + 1][x]);
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

//doesn't need to be a function?
int	check_color(t_vector point, t_coord start, t_coord end, t_vector delta)
{
	int red, green, blue;
	int red1, green1, blue1;
	int red2, green2, blue2;
	float norm, lerp;

	if (delta.x > delta.y)
		norm = ft_norm(point.x, start.vect.x, end.vect.x);
	else
		norm = ft_norm(point.x, start.vect.x, end.vect.x);
	
	//printf("norm = %f\n", norm);

	red1 = (start.color >> 16) & 0xFF;
	red2 = (end.color >> 16) & 0xFF;
	green1 = (start.color >> 8) & 0xFF;
	green2 = (end.color >> 8) & 0xFF;
	blue1 = start.color & 0xFF;
	blue2 = end.color & 0xFF;
	red = ft_lerp(norm, red1, red2);
	green = ft_lerp(norm, green1, green2);
	blue = ft_lerp(norm, blue1, blue2);

	return ((red << 16) | (green << 8) | blue);
}

