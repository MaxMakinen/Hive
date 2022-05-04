/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:01:50 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 13:43:12 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_circle(t_utils *utils, t_2d coords, int radius, int color)
{
	int	x2;
	int	y2;
	int	l;

	l = (int)radius * cos(PI / 4);
	x2 = 0;
	while (x2 <= l)
	{
		y2 = (int)sqrt((double)(radius * radius) - (x2 * x2));
		ft_pixel_put(utils, x2 + coords.a, -y2 + coords.b, color);
		ft_pixel_put(utils, y2 + coords.a, -x2 + coords.b, color);
		ft_pixel_put(utils, y2 + coords.a, x2 + coords.b, color);
		ft_pixel_put(utils, x2 + coords.a, y2 + coords.b, color);
		ft_pixel_put(utils, -x2 + coords.a, y2 + coords.b, color);
		ft_pixel_put(utils, -y2 + coords.a, x2 + coords.b, color);
		ft_pixel_put(utils, -y2 + coords.a, -x2 + coords.b, color);
		ft_pixel_put(utils, -x2 + coords.a, -y2 + coords.b, color);
		x2++;
	}
}

void	draw_quadrilateral(t_utils *utils, t_quadril *xy, int color)
{
	draw_line(utils, &(t_line){xy->a, xy->b, xy->c, xy->d}, color, color);
	draw_line(utils, &(t_line){xy->c, xy->d, xy->e, xy->f}, color, color);
	draw_line(utils, &(t_line){xy->e, xy->f, xy->g, xy->h}, color, color);
	draw_line(utils, &(t_line){xy->g, xy->h, xy->a, xy->b}, color, color);
}

void	draw_square(t_utils *utils, t_line *xy, int color)
{
	int	size_x;
	int	size_y;

	size_x = xy->x - xy->x_dest;
	size_y = xy->y - xy->y_dest;
	draw_line(utils, &(t_line){xy->x, xy->y, xy->x_dest,
		xy->y_dest}, color, color);
	draw_line(utils, &(t_line){xy->x_dest,
		xy->y_dest, xy->x_dest + size_y, xy->y_dest - size_x}, color, color);
	draw_line(utils, &(t_line){xy->x + size_y, xy->y - size_x,
		xy->x_dest + size_y, xy->y_dest - size_x}, color, color);
	draw_line(utils, &(t_line){xy->x, xy->y,
		xy->x + size_y, xy->y - size_x}, color, color);
}
