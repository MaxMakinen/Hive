/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_key_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:47:17 by deelliot          #+#    #+#             */
/*   Updated: 2022/09/07 10:51:30 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	handle_translation(int key, t_win *win)
{
	int	inc;

	if (win->fractol_option == 6)
		inc = 1;
	else
		inc = 10;
	if (key == UP)
		win->y_offset += inc;
	if (key == DOWN)
		win->y_offset -= inc;
	if (key == LEFT)
		win->x_offset += inc;
	if (key == RIGHT)
		win->x_offset -= inc;
	mlx_clear_window(win->mlx, win->win);
	execute_image(win);
}

void	handle_colour(t_win *win)
{
	win->colour += 1;
	if (win->colour == 5)
		win->colour = 0;
	mlx_clear_window(win->mlx, win->win);
	execute_image(win);
}

void	handle_iterations(int key, t_win *win)
{
	if (key == ITER_UP)
		win->max_iter += 10;
	if (key == ITER_DOWN)
	{
		if (win->max_iter > 10)
			win->max_iter -= 10;
	}
	mlx_clear_window(win->mlx, win->win);
	execute_image(win);
}

void	handle_power(t_win *win)
{
	win->power += 1;
	if (win->power == 10)
		win->power = -5;
	if (win->power == -1)
		win->power = 2;
	mlx_clear_window(win->mlx, win->win);
	execute_image(win);
}

void	handle_reset(t_win *win)
{
	win->zoom = 0.0;
	win->colour = 0;
	win->mouse_x = -0.7269;
	win->mouse_y = 0.1889;
	win->lock = 1;
	win->power = 3;
	fractal_positions(win);
	mlx_clear_window(win->mlx, win->win);
	execute_image(win);
}
