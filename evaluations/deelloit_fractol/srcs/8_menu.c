/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_menu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:06:49 by deelliot          #+#    #+#             */
/*   Updated: 2022/09/07 10:56:47 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	side_menu(t_win *win)
{
	char	*iterations;
	char	*power;

	iterations = ft_itoa(win->max_iter);
	if (!iterations)
		handle_errors(win);
	power = ft_itoa(win->power);
	if (!power)
		handle_errors(win);
	if (win->fractol_option == 2 || win->fractol_option == 3)
	{
		mlx_string_put(win->mlx, win->win, 1190, 40, 0xFFFFFF, "power: ");
		mlx_string_put(win->mlx, win->win, 1250, 40, 0xFFFFFF, power);
	}
	mlx_string_put(win->mlx, win->win, 1190, 20, 0xFFFFFF, iterations);
	free (iterations);
	free (power);
}

void	window_menu(t_win *win)
{
	char	*str[9];
	int		i;

	str[0] = "MOVE:            W, S, A, D";
	str[1] = "ZOOM:            I and O / MOUSE SCROLL";
	str[2] = "COLOUR:          SPACE";
	str[3] = "RESET:           ENTER";
	str[4] = "ITERATIONS:      ARROW UP & DOWN";
	str[5] = "CHANGE POWER     P";
	str[6] = "LOCK JULIA       LEFT CLICK";
	str[7] = "CHANGE FRACTOL   RIGHT CLICK";
	str[8] = "QUIT:            ESC";
	i = 0;
	while (i < 9)
	{
		mlx_string_put(win->mlx, win->win, 20, 20 + (i * 15), 0xFFFFFF, str[i]);
		i++;
	}
	side_menu(win);
}
