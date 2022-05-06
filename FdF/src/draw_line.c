/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:30:54 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/06 10:22:50 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	increment_x(t_data *data, t_coord *start, t_coord *end, \
		t_d_tools *tools)
{
	while (tools->current.x++ < tools->current.z)
	{
		if (tools->check.x < 0)
			tools->check.x += 2 * tools->abs_delta.y;
		else
		{
			tools->current.y += tools->check.z;
			tools->check.x += 2 * (tools->abs_delta.y - tools->abs_delta.x);
		}
		if (in_window(&tools->current))
			img_pix_put(data->img, tools->current.x, tools->current.y, \
					check_color(&tools->current, start, end, &tools->delta));
	}
}

void	increment_y(t_data *data, t_coord *start, t_coord *end, \
		t_d_tools *tools)
{
	while (tools->current.y++ < tools->current.z)
	{
		if (tools->check.y <= 0)
			tools->check.y += 2 * tools->abs_delta.x;
		else
		{
			tools->current.x += tools->check.z;
			tools->check.y += 2 * (tools->abs_delta.x - tools->abs_delta.y);
		}
		if (in_window(&tools->current))
			img_pix_put(data->img, tools->current.x, tools->current.y, \
					check_color(&tools->current, start, end, &tools->delta));
	}
}

int	draw_line(t_data *data, t_coord *start, t_coord *end)
{
	t_d_tools	d_tools;

	if (start->visible == 0 || end->visible == 0)
		return (1);
	d_tools.delta = get_delta(start->vect, end->vect);
	d_tools.abs_delta = abs_vector(d_tools.delta);
	d_tools.check.x = 2 * d_tools.abs_delta.y - d_tools.abs_delta.x;
	d_tools.check.y = 2 * d_tools.abs_delta.x - d_tools.abs_delta.y;
	if ((d_tools.delta.x < 0 && d_tools.delta.y < 0) || \
			(d_tools.delta.x > 0 && d_tools.delta.y > 0))
		d_tools.check.z = 1;
	else
		d_tools.check.z = -1;
	d_tools.current = find_current(&start->vect, &end->vect, &d_tools);
	if (in_window(&d_tools.current))
		img_pix_put(data->img, d_tools.current.x, d_tools.current.y, \
				rgb_int(start->color));
	if (d_tools.abs_delta.y <= d_tools.abs_delta.x)
		increment_x(data, start, end, &d_tools);
	else
		increment_y(data, start, end, &d_tools);
	return (1);
}
