/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:35:16 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/11 14:18:55 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	if (data->win_ptr == NULL)
		return (1);
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			img_pix_put(data->img, x, y, mandel(x ,y));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
			data->img->mlx_img, 0, 0);
	return (0);
}

int	get_color(int iteration)
{
	union u_color color;

	color.color = 0;
	if (iteration == 200)
		return (color.color);
//	color.rgb[1] = iteration % 255;
//	iteration -= iteration % 255;
	color.color = iteration;
//	printf("%d", iteration);
	return (color.color);
}

int	mandel(int pixel_x, int pixel_y)
{
	double	scaled_x; //scaled X coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.00, 0.47))
	double scaled_y; //scaled Y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1.12, 1.12))
	double	x;
	double	y;
	int	iteration;
	int	max_iteration;

	pixel_x++;
	pixel_y++;
	scaled_x = (double)(ft_lerp(ft_norm(pixel_x, 0.0, WINDOW_WIDTH), -2.00, 0.47));
	scaled_y = (double)(ft_lerp(ft_norm(pixel_y, 0.0, WINDOW_HEIGHT), -1.12, 1.12));
	x = 0;
	y = 0;
	iteration = 0;
	max_iteration = 200;

	double	xtemp;
	while (((x * x + y * y) <= 2 * 2) && iteration < max_iteration)
	{
		xtemp = x * x - y * y + scaled_x;
		y = 2 * x * y + scaled_y;
		x = xtemp;
		iteration++;
	}
	return (get_color(iteration));
}

