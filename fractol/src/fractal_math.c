/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:35:16 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/12 15:02:15 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	get_color(t_data *data, int iteration)
{
	union u_color color;

	color.color = 0;
	if (iteration == data->max_iterations)
		return (color.color);
	/*
	color.rgb[0] = iteration % 255;
	iteration -= iteration % 255;
	color.rgb[1] = iteration % 255;
	iteration -= iteration % 255;
	color.rgb[2] = iteration % 255;
	iteration -= iteration % 255;
	*/
	
	color.rgb[1] = (int)((0.5f * sin(0.1f * iteration) + 0.5f) * 255.0f);
	color.rgb[2] = (int)((0.5f * sin(0.1f * iteration + 2.094f) + 0.5f) * 255.0f);
	color.rgb[3] = (int)((0.5f * sin(0.1f * iteration + 4.188f) + 0.5f) * 255.0f);
	
	return (color.color);
}
/*
int	mandel(int pixel_x, int pixel_y)
{
	double	scaled_x; //scaled X coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.00, 0.47))
	double scaled_y; //scaled Y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1.12, 1.12))
	double	x;
	double	y;
	int	iteration;
	int	max_iteration;

	scaled_x = (double)(ft_lerp(ft_norm(pixel_x, 0.0, (float)WINDOW_WIDTH), -2.00, 1.00));
	scaled_y = (double)(ft_lerp(ft_norm(pixel_y, 0.0, (float)WINDOW_HEIGHT), -1.00, 1.00));
	x = 0;
	y = 0;
	iteration = 0;
	max_iteration = 200;

	double	xtemp;
	while ((x * x + y * y) <= 4.0 && iteration < max_iteration)
	{
		xtemp = x * x - y * y + scaled_x;
		y = 2 * x * y + scaled_y;
		x = xtemp;
		iteration++;
	}
	return (get_color(iteration));
}
*/
