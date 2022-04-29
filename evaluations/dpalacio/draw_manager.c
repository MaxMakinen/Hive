/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:51:12 by dpalacio          #+#    #+#             */
/*   Updated: 2022/04/28 16:31:32 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Creates images to put in the window for the wireframe and ui
void	draw(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		error_print("Error(4): Image not allocated", data);
	data->img_addr = mlx_get_data_addr(data->img, &data->px_bits,
			&data->line_bytes, &data->endian);
	if (!data->img_addr)
		error_print("Error(4): Image address not allocated", data);
	draw_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		error_print("Error(4): Image not allocated", data);
	data->img_addr = mlx_get_data_addr(data->img, &data->px_bits,
			&data->line_bytes, &data->endian);
	if (!data->img_addr)
		error_print("Error(4): Image address not allocated", data);
	draw_ui(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	display_controls(data);
	mlx_destroy_image(data->mlx, data->img);
	data->img = NULL;
	data->img_addr = NULL;
}

//Colors each given pixel guarding that it never leaves the image
void	img_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	if (data->px_bits != 32)
		color = mlx_get_color_value(data->mlx, color);
	if (x < WIN_WIDTH && y < WIN_HEIGHT && x >= 0 && y >= 0)
	{
		pixel = data->img_addr + (y * data->line_bytes)
			+ (x * (data->px_bits / 8));
		if (pixel == NULL)
			error_print("Error(6): Bad allocated pixel", data);
		*(unsigned int *)pixel = color;
	}
}

//Choses and colors every pixel forming a straight line between two points
int	draw_line(t_line line, t_data *data, int c0, int c1)
{
	float	dx;
	float	dy;
	int		step;
	float	x;
	float	y;

	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	x = line.x0;
	y = line.y0;
	if (ft_abs(dx) >= ft_abs(dy))
		step = ft_abs(dx);
	else
		step = ft_abs(dy);
	dx = dx / step;
	dy = dy / step;
	while (step >= 0)
	{
		img_pixel_put(data, x, y, color_gradient(c0, c1, step));
		c0 = color_gradient(c0, c1, step);
		x = x + dx;
		y = y + dy;
		step--;
	}
	return (1);
}

//Moves the start of the map drawing to center it on screen
void	offset_draw(t_data *data)
{
	data->y_off = WIN_HEIGHT / 6;
	data->zoom = (WIN_HEIGHT - 2 * data->y_off) / data->map_height;
	data->x_off = (WIN_WIDTH - data->map_width * data->zoom) / 2;
}
