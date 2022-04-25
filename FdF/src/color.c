/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:49:34 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/25 10:29:25 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	return ((num - min) / (max - min));
}

float ft_lerp(float norm, float min, float max)
{
	return ((max-min) * norm + min);
}

int	check_color(t_vector point, t_coord start, t_coord end, t_vector delta)
{
	int red, green, blue;
	int red1, green1, blue1;
	int red2, green2, blue2;
	int	min, max;
	float norm, lerp;

	if (delta.x > delta.y)
	{
		norm = ft_norm(point.x, start.vect.x, end.vect.x);
		min = start.vect.x;
		max = end.vect.x;
	}
	else
	{
		norm = ft_norm(point.x, start.vect.x, end.vect.x);
		min = start.vect.y;
		max = end.vect.y;
	}
	
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

int	g_col(t_rgb rgb, t_rgb step, int pos)
{
	if (pos == 0)
		return ((rgb.red << 16) | (rgb.green << 8) | rgb.blue);
	rgb.red = step.red * pos;
	rgb.green = step.green * pos;
	rgb.blue = step.blue * pos;
	return ((rgb.red << 16) | (rgb.green << 8) | rgb.blue);
}
