/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:30:54 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/05 15:40:57 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	increment_x(t_data *data, t_coord *start, t_coord *end, t_intvec \
		*current, t_intvec *delta, t_intvec *abs_delta, t_intvec *check)
{
	while ((*current).x++ < (*current).z)
	{
		if ((*check).x < 0)
			(*check).x += 2 * (*abs_delta).y;
		else
		{
			(*current).y += (*check).z;
			(*check).x += 2 * ((*abs_delta).y - (*abs_delta).x);
		}
		if (in_window(current))
			img_pix_put(data->img, (*current).x, (*current).y, \
					check_color(current, start, end, delta));
	}
}

void	increment_y(t_data *data, t_coord *start, t_coord *end, t_intvec \
		*current, t_intvec *delta, t_intvec *abs_delta, t_intvec *check)
{
	while ((*current).y++ < (*current).z)
	{
		if ((*check).y <= 0)
			(*check).y += 2 * (*abs_delta).x;
		else
		{
			(*current).x += (*check).z;
			(*check).y += 2 * ((*abs_delta).x - (*abs_delta).y);
		}
		if (in_window(current))
			img_pix_put(data->img, (*current).x, (*current).y, \
					check_color(current, start, end, delta));
	}
}

int	draw_line(t_data *data, t_coord *start, t_coord *end)
{
	t_intvec	delta;
	t_intvec	abs_delta;
	t_intvec	current;
	t_intvec	check;

	if (start->visible == 0 || end->visible == 0)
		return (1);
	delta = get_delta(start->vect, end->vect);
	abs_delta = abs_vector(delta);
	check.x = 2 * abs_delta.y - abs_delta.x;
	check.y = 2 * abs_delta.x - abs_delta.y;
	if ((delta.x < 0 && delta.y < 0) || (delta.x > 0 && delta.y > 0))
		check.z = 1;
	else
		check.z = -1;
	current = find_current(&start->vect, &end->vect, &abs_delta, &delta);
	if (in_window(&current))
		img_pix_put(data->img, current.x, current.y, rgb_int(start->color));
	if (abs_delta.y <= abs_delta.x)
		increment_x(data, start, end, &current, &delta, &abs_delta, &check);
	else
		increment_y(data, start, end, &current, &delta, &abs_delta, &check);
	return (1);
}
