/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:41:48 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/05 16:13:57 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	in_window(t_intvec *vector)
{
	if (vector->x < WINDOW_WIDTH && vector->x > 0)
	{
		if (vector->y < WINDOW_HEIGHT && vector->y > 0)
			return (TRUE);
	}
	return (FALSE);
}

int	getcol(t_rgb start, t_rgb end, int delta, int step)
{
	t_rgb	new;

	new.red = ((step / delta) * start.red) + \
				(((delta - step) / delta) * end.red);
	new.green = ((step / delta) * start.green) + \
				(((delta - step) / delta) * end.green);
	new.blue = ((step / delta) * start.blue) + \
				(((delta - step) / delta) * end.blue);
	return (rgb_int(new));
}

t_intvec	find_current(t_vector *start, t_vector *end, t_d_tools *d_tools)
{
	if (d_tools->abs_delta.y <= d_tools->abs_delta.x)
		return (get_current(start, end, d_tools->delta.x, 1));
	else
		return (get_current(start, end, d_tools->delta.y, 0));
}

t_intvec	get_current(t_vector *start, t_vector *end, int delta, int dir)
{
	t_intvec	current;

	if (delta >= 0)
	{
		current.x = start->x;
		current.y = start->y;
		if (dir == 1)
			current.z = end->x;
		else
			current.z = end->y;
	}
	else
	{
		current.x = end->x;
		current.y = end->y;
		if (dir == 1)
			current.z = start->x;
		else
			current.z = start->y;
	}
	return (current);
}
