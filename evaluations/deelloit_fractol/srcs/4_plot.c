/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:11:14 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:18:18 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* loops through each pixel of the window, passes coordinates to fractol fn,
which calculates whether that coordinate value remains bounded or not. Then
uses the return value to set colour and place pixel in image*/

int	pick_fractal(t_win *win, int x, int y)
{
	int	n;

	if (win->fractol_option == 0)
		n = julia(win, x, y);
	else if (win->fractol_option == 1)
		n = mandelbrot(win, x, y);
	else if (win->fractol_option == 2)
		n = multibrot(win, x, y);
	else if (win->fractol_option == 3)
		n = multijulia(win, x, y);
	else if (win->fractol_option == 4)
		n = tricorn(win, x, y);
	else
		n = burningship(win, x, y);
	return (n);
}

void	*plot_points(void *thread_data)
{
	int			x;
	int			y;
	t_thread	*thread;
	int			n;

	thread = (t_thread *)thread_data;
	y = -1;
	while (++y < HEIGHT)
	{
		x = (thread->start) - 1;
		while (++x < thread->end)
		{
			n = pick_fractal(thread->win, x, y);
			img_pixel_put(n, x, y, thread->win);
		}
	}
	return (NULL);
}
