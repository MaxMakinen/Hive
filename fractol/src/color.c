/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:35:16 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/25 09:44:23 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color_bw(t_data *data, int iteration)
{
	union u_color	color;

	iteration += ((data->max_iterations - iteration) * 0.1);
	color.rgb[0] = (int)(ft_norm(iteration, 0.0, data->max_iterations) \
			* 255.0f);
	color.rgb[1] = color.rgb[0];
	color.rgb[2] = color.rgb[0];
	color.rgb[3] = 0;
	return (color.color);
}

int	color_rainbow(t_data *data, int iteration)
{
	union u_color	color;

	color.rgb[0] = (int)((0.5f * sin(0.1f * iteration) + 0.5f) * 255.0f);
	color.rgb[1] = (int)((0.5f * sin(0.1f * iteration + 2.094f) + 0.5f) \
			* 255.0f);
	color.rgb[2] = (int)((0.5f * sin(0.1f * iteration + 4.188f) + 0.5f) \
			* 255.0f);
	color.rgb[3] = 0;
	return (color.color);
}

int	color_carnival(t_data *data, int iteration)
{
	union u_color	color;

	color.rgb[0] = (int)((0.5f * sin(iteration) + 0.1f) * 255.0f);
	color.rgb[1] = (int)((0.5f * sin(iteration + 2.0f) + 0.1f) * 255.0f);
	color.rgb[2] = (int)((0.5f * sin(iteration + 4.0f) + 0.1f) * 255.0f);
	color.rgb[3] = 0;
	return (color.color);
}

int	color_carnival_bw(t_data *data, int iteration)
{
	union u_color	color;

	color.rgb[0] = (int)((0.5f * sin(iteration) + 0.1f) * 255.0f);
	color.rgb[1] = color.rgb[0];
	color.rgb[2] = color.rgb[0];
	color.rgb[3] = 0;
	return (color.color);
}

int	get_color(t_data *data, int iteration)
{
	if (iteration == data->max_iterations)
		return (0);
	if (data->color == 0)
		return (color_rainbow(data, iteration));
	if (data->color == 1)
		return (color_bw(data, iteration));
	if (data->color == 2)
		return (color_carnival(data, iteration));
	if (data->color == 3)
		return (color_carnival_bw(data, iteration));
	return (0);
}
