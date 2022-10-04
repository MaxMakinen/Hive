/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_fractal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:03:23 by deelliot          #+#    #+#             */
/*   Updated: 2022/09/07 10:55:24 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* f(z) = (z * z) + c, where c = a + bi.
 f[{x, y}] = {(a^2 - b^2) + c1}, {2xy + c2}
A complex number () can be represented on a complex plane.
The real part of the complex number is represented by a displacement along
the x-axis and the imaginary part by a displacement along the y-axis. */

int	julia(t_win *win, int x, int y)
{
	t_complex	z;
	t_complex	c;
	double		temp;
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
		temp = (z.real * z.real) - (z.imag * z.imag);
		z.imag = (2 * z.real * z.imag) + c.imag;
		z.real = temp + c.real;
		n++;
	}
	return (n);
}

int	mandelbrot(t_win *win, int x, int y)
{
	t_complex	z;
	t_complex	c;
	double		temp;
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
		temp = (z.real * z.real) - (z.imag * z.imag);
		z.imag = (2 * z.real * z.imag) + c.imag;
		z.real = temp + c.real;
		n++;
	}
	return (n);
}

int	tricorn(t_win *win, int x, int y)
{
	t_complex	z;
	t_complex	c;
	double		temp;
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
		temp = (z.real * z.real) - (z.imag * z.imag);
		z.imag = -2 * z.real * z.imag + c.imag;
		z.real = temp + c.real;
		n++;
	}
	return (n);
}
/* same as mandelbrot except real and imaginery component set to absolute
value before each iteration calculation */

int	burningship(t_win *win, int x, int y)
{
	t_complex	z;
	t_complex	c;
	double		temp;
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
		z.real = fabs(z.real);
		z.imag = fabs(z.imag);
		temp = (z.real * z.real) - (z.imag * z.imag);
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp + c.real;
		n++;
	}
	return (n);
}
