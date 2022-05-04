/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:19:04 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 15:19:21 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_draw_line_vars(int *x_len, int *y_len, int *i, int *check)
{
	*i = 1;
	if (*y_len < 0)
	{
		*i = -1;
		*y_len = -(*y_len);
	}
	*check = (2 * (*y_len) - (*x_len));
}

void	draw_line_down(t_utils *utils, t_line *line, int color, int dest_color)
{
	int		x_len;
	int		y_len;
	int		i;
	int		check;
	float	percent;

	x_len = line->x_dest - line->x;
	y_len = line->y_dest - line->y;
	init_draw_line_vars(&x_len, &y_len, &i, &check);
	while (line->x <= line->x_dest)
	{
		percent = (float)(line->x - (line->x_dest - x_len)) / x_len;
		if (x_len)
			utils->mix_color = mix_colors(color, dest_color, percent);
		ft_pixel_put(utils, line->x, line->y, utils->mix_color);
		if (check >= 0)
		{
			line->y = line->y + i;
			check = check + (2 * (y_len - x_len));
		}
		else
			check = check + (2 * y_len);
		line->x++;
	}
}

void	draw_line_up(t_utils *utils, t_line *line, int color, int dest_color)
{
	int		x_len;
	int		y_len;
	int		i;
	int		check;
	float	percent;

	x_len = line->x_dest - line->x;
	y_len = line->y_dest - line->y;
	init_draw_line_vars(&y_len, &x_len, &i, &check);
	while (line->y <= line->y_dest)
	{
		percent = (float)(line->y - (line->y_dest - y_len)) / y_len;
		if (y_len)
			utils->mix_color = mix_colors(color, dest_color, percent);
		ft_pixel_put(utils, line->x, line->y, utils->mix_color);
		if (check >= 0)
		{
			line->x = line->x + i;
			check = check + (2 * (x_len - y_len));
		}
		else
			check = check + (2 * x_len);
		line->y++;
	}
}

void	draw_line(t_utils *utils, t_line *line, int color, int dest_color)
{
	if (abs(line->y_dest - line->y) < abs(line->x_dest - line->x))
	{
		if (line->x > line->x_dest)
			draw_line_down(utils, &(t_line){line->x_dest, line->y_dest,
				line->x, line->y}, dest_color, color);
		else
			draw_line_down(utils, &(t_line){line->x, line->y,
				line->x_dest, line->y_dest}, color, dest_color);
	}
	else
	{
		if (line->y > line->y_dest)
			draw_line_up(utils, &(t_line){line->x_dest, line->y_dest,
				line->x, line->y}, dest_color, color);
		else
			draw_line_up(utils, &(t_line){line->x, line->y,
				line->x_dest, line->y_dest}, color, dest_color);
	}
}
