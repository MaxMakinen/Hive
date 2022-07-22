/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:35:16 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/22 17:51:21 by mmakinen         ###   ########.fr       */
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
	union u_color	color;

	color.color = 0;
	if (iteration == data->max_iterations)
		return (color.color);
	if (data->color == 0)
	{
		iteration += ((data->max_iterations - iteration) * 0.1);
		color.rgb[0] = (int)(ft_norm(iteration, 0.0, data->max_iterations) * 255.0f);
		color.rgb[1] = color.rgb[0];
		color.rgb[2] = color.rgb[0];
		color.rgb[3] = 0;
	}
	if (data->color == 3)
	{
		color.rgb[0] = (int)((0.5f * sin(iteration) + 0.1f) * 255.0f);
		color.rgb[1] = color.rgb[0];
		color.rgb[2] = color.rgb[0];
		color.rgb[3] = 0;
	}
	if (data->color == 2)
	{
		color.rgb[0] = (int)((0.5f * sin(iteration) + 0.1f) * 255.0f);
		color.rgb[1] = (int)((0.5f * sin(iteration + 2.0f) + 0.1f) * 255.0f);
		color.rgb[2] = (int)((0.5f * sin(iteration + 4.0f) + 0.1f) * 255.0f);
		color.rgb[3] = 0;
	}
	if (data->color == 1)
	{	
		color.rgb[0] = (int)((0.5f * sin(0.1f * iteration) + 0.5f) * 255.0f);
		color.rgb[1] = (int)((0.5f * sin(0.1f * iteration + 2.094f) + 0.5f) * 255.0f);
		color.rgb[2] = (int)((0.5f * sin(0.1f * iteration + 4.188f) + 0.5f) * 255.0f);
		color.rgb[3] = 0;
	}
	return (color.color);
}
