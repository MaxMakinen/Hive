/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multibrot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:27:49 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 13:40:34 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	multibrot(t_win *win, int x, int y)
{
	t_complex	z;
	t_complex	c;
	double		temp;
	double		num;
	int			n;

	z.real = ft_linear_conversion(win->width_range, win->x_range, \
		x + win->x_offset);
	z.imag = ft_linear_conversion(win->height_range, win->y_range, \
		y + win->y_offset);
	c.real = z.real;
	c.imag = z.imag;
	n = 0;
	while (n < win->max_iter && (z.real * z.real) + \
		(z.imag * z.imag) < 4)
	{
		temp = z.real * z.real + z.imag * z.imag;
		num = win->power * atan2(z.imag, z.real);
		z.imag = pow(temp, (win->power / 2)) * sin(num) + c.imag;
		z.real = pow(temp, (win->power / 2)) * cos(num) + c.real;
		n++;
	}
	return (n);
}

int	multijulia(t_win *win, int x, int y)
{
	t_complex	z;
	t_complex	c;
	double		temp;
	double		num;
	int			n;

	z.real = ft_linear_conversion(win->width_range, win->x_range, \
		x + win->x_offset);
	z.imag = ft_linear_conversion(win->height_range, win->y_range, \
		y + win->y_offset);
	c.real = win->mouse_x;
	c.imag = win->mouse_y;
	n = 0;
	while (n < win->max_iter && (z.real * z.real) + \
		(z.imag * z.imag) < 4)
	{
		temp = z.real * z.real + z.imag * z.imag;
		num = win->power * atan2(z.imag, z.real);
		z.imag = pow(temp, (win->power / 2)) * sin(num) + c.imag;
		z.real = pow(temp, (win->power / 2)) * cos(num) + c.real;
		n++;
	}
	return (n);
}
