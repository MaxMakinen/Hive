/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:43 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/20 16:36:49 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int num)
{
	if (num < -2147483648)
		return (2147483647);
	if (num < 0)
		num = -num;
	return (num);
}

int handle_keypress(int keysym, t_data *data)
{
	if (keysym == 113)
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
	float	temp;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
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

t_matrix	*mat_mul(t_matrix *matrix, t_matrix *vector)
{
	int		rows;
	int		cols;
	int		index;
	int		len;
	int		sum;
	t_matrix	*result;

	rows = 0;
	len = 3;
	result = prep_matrix();
	while (rows < len)
	{
		cols = 0;
		while (cols < len)
		{
			index = 0;
			sum = 0;
			while (index < len)
			{
				sum += matrix->matrix[rows][index] * vector->matrix[index][cols];
				index++;
			}
			result->matrix[rows][cols] += sum;
			cols++;
		}
		rows++;
	}
	return (result);
}


int	check_color(t_vector coord)
{
	if (coord.z > 0)
		return (GREEN_PIXEL);
	return (RED_PIXEL);
}

int	render_line(t_img *img, t_vector start, t_vector end)
{
	int	x;
	int	y;
	int	m;
	int delta;
	int	adjust;
	int	offset;
	int	threshold;
	int	threshold_inc;
	t_vector dist;

	dist.x = start.x - end.x;
	dist.y = start.y - end.y;
	if (dist.x == 0)
	{
		if (end.y < start.y)
			ft_swapint(&start.y, &end.y);
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
			delta= ft_abs(dist.x) * 2;
			threshold = ft_abs(dist.y);
			threshold_inc = ft_abs(dist.y) * 2;
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

t_map *project(t_map *map, t_matrix *matrix)
{
    int x;
    int y;
    t_matrix    *temp;

    y = 0;
    while (y < map->y_max)
    {
        x = 0;
        while (x < map->x_max)
        {
            temp = vec_to_matrix(&map->coords[y][x].vect);
            mat_mul(matrix, temp);
            map->coords[y][x].vect = *matrix_to_vec(temp);
            x++;
        }
        y++;
    }
    return (map);
}

int render(t_data *data)
{
	int	x;
	int	y;
	int	placement;

	y = 0;
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, BLACK_PIXEL);
	data->map = *project(&data->map, projection_matrix());
	while (y < data->map.y_max)
	{
		x = 0;
		while (x < data->map.x_max)
		{
			if((x + 1) < data->map.x_max)
				render_line(&data->img, vect_mult(data->map.coords[y][x].vect, OFFSET), vect_mult(data->map.coords[y][x + 1].vect, OFFSET));
			if((y + 1) < data->map.y_max)
				render_line(&data->img, vect_mult(data->map.coords[y][x].vect, OFFSET), vect_mult(data->map.coords[y + 1][x].vect, OFFSET));
			x++;
		}
		y++;
	}
	
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}


