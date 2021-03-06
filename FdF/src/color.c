/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:49:34 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/05 15:37:50 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_percent(int num, int min, int max)
{
	double	diff;
	double	range;

	diff = num - min;
	range = max - min;
	if (diff == 0)
		return (1.0);
	return (diff / range);
}

int	rgb_int(t_rgb rgb)
{
	return ((rgb.red << 16) | (rgb.green << 8) | rgb.blue);
}

t_rgb	int_rgb(int col)
{
	t_rgb	rgb;

	rgb.red = (col >> 16) & 0xFF;
	rgb.green = (col >> 8) & 0xFF;
	rgb.blue = col & 0xFF;
	return (rgb);
}

int	check_color(t_intvec *point, t_coord *start, t_coord *end, t_intvec *delta)
{
	t_rgb	new;
	float	norm;

	if (delta->x > delta->y)
		norm = ft_norm(point->x, start->vect.x, end->vect.x);
	else
		norm = ft_norm(point->y, start->vect.y, end->vect.y);
	new.red = ft_lerp(norm, start->color.red, end->color.red);
	new.green = ft_lerp(norm, start->color.green, end->color.green);
	new.blue = ft_lerp(norm, start->color.blue, end->color.blue);
	return (rgb_int(new));
}
