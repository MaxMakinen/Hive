/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:38:41 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/02 10:35:44 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float ft_pyth(float a, float b)
{
	return (sqrtf(powf(a, 2) + powf(b, 2)));
}

t_intvec get_delta(t_vector start, t_vector end)
{
	t_intvec	delta;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	delta.z = end.z - start.z;
	return (delta);
}

t_intvec abs_vector(t_intvec intvec)
{
	intvec.x = ft_abs(intvec.x);
	intvec.y = ft_abs(intvec.y);
	intvec.z = ft_abs(intvec.z);
	return (intvec);
}

t_intvec get_current(t_vector start, t_vector end, int delta, int dir)
{
	t_intvec	current;

	if (delta >= 0)
	{
		current.x = start.x;
		current.y = start.y;
		if (dir == 1)
			current.z = end.x;
		else
			current.z = end.y;
	}
	else
	{
		current.x = end.x;
		current.y = end.y;
		if (dir == 1)
			current.z = start.x;
		else
			current.z = start.y;
	}
	return (current);
}

int in_window(t_intvec vector)
{
	if (vector.x < WINDOW_WIDTH && vector.x > 0)
	{
		if (vector.y < WINDOW_HEIGHT && vector.y > 0)
			return (TRUE);
	}
	return (FALSE);
}

int	getcol(t_rgb start, t_rgb end, int delta, int step)
{
	t_rgb	new;

	new.red = ((step / delta) * start.red) + (((delta - step) / delta) * end.red);
	new.green = ((step / delta) * start.green) + (((delta - step) / delta) * end.green);
	new.blue = ((step / delta) * start.blue) + (((delta - step) / delta) * end.blue);
	return (rgb_int(new));
}

int draw_line(t_data *data, t_coord start, t_coord end)
{
	t_intvec	delta;
	t_intvec	abs_delta;
	t_intvec	current;
	t_intvec	check;

	if (start.visible == 0 || end.visible == 0)
		return (1);
	delta = get_delta(start.vect, end.vect);
	abs_delta = abs_vector(delta);
	check.x = 2 * abs_delta.y - abs_delta.x;
	check.y = 2 * abs_delta.x - abs_delta.y;
	if ((delta.x < 0 && delta.y < 0) || (delta.x > 0 && delta.y > 0))
		check.z = 1;
	else
		check.z = -1;
	if (abs_delta.y <= abs_delta.x)
	{
		current = get_current(start.vect, end.vect, delta.x, 1);
		if (in_window(current))
			img_pix_put(&data->img, current.x, current.y, rgb_int(start.color));
		while (current.x < current.z)
		{
			current.x += 1;
			if (check.x < 0)
				check.x += 2 * abs_delta.y;
			else
			{
				current.y += check.z;
				check.x += 2 * (abs_delta.y - abs_delta.x);
			}
			if (in_window(current))
				img_pix_put(&data->img, current.x, current.y, check_color(current, start, end, delta));
		}
	}
	else
	{
		current = get_current(start.vect, end.vect, delta.y, 0);
		if (in_window(current))
			img_pix_put(&data->img, current.x, current.y, rgb_int(start.color));
		while (current.y < current.z)
		{
			current.y += 1;
			if (check.y <= 0)
				check.y += 2 * abs_delta.x;
			else
			{
				current.x += check.z;
				check.y += 2 * (abs_delta.x - abs_delta.y);
			}
			if (in_window(current))
				img_pix_put(&data->img, current.x, current.y, check_color(current, start, end, delta));
		}
	}
	return (1);
}

int render(t_data *data)
{
	int	x;
	int	y;


	y = 0;
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, 0x202020);
	while (y < data->map.y_max)
	{
		x = 0;
		while (x < data->map.x_max)
		{
			if((x + 1) < data->map.x_max)
				draw_line(data, data->map.vec[y][x], data->map.vec[y][x + 1]);
			if((y + 1) < data->map.y_max)
				draw_line(data, data->map.vec[y][x], data->map.vec[y + 1][x]);
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

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}
/*
void img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
*/
		/* img versions */

void render_background(t_img *img, int color)
{
//	int	i;
	int	*pixel;
//	int size;
	int x, y = 0;

	pixel = (int *)img->addr;
/*	size = WINDOW_HEIGHT * WINDOW_WIDTH;
	i = 0;
	ft_memset(img->addr, 0, size * (img->bpp / 8));
	while (i < size)
	{
		pixel[i] = color;
		i++;
	}
*/
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
			img_pix_put(img, x++, y, color);
		y++;
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

