/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:57:05 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/26 15:28:23 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "the_uncontrolled_element_of_life.h"
#define MAX 30

// For the sake of reading clarity, the variables during 'draw_fractal()'
// that have an adjust for the user request are set here.

void	request_adjust(t_fract *f)
{
	if (f->request == JULIA)
	{
		f->z_x = f->c_x;
		f->z_y = f->c_y;
		f->c_x = f->mouse_x;
		f->c_y = f->mouse_y;
	}
	else if (f->request == MANDELBROT || f->request == TRICORN)
	{
		f->c_x += f->mouse_x;
		f->c_y += f->mouse_y;
		f->z_x = 0;
		f->z_y = 0;
	}
	if (f->request == TRICORN)
		f->fractal_toggle = -2;
	else
		f->fractal_toggle = 2;
}

// Bitwise operation for applying the fractal iteration ('count') to color.
// Count multiplied by 10 sets the highest color to red. Middle shades (* 8)
// are bitwise folded to green-ish. And the lowest multiplier is set to blue.

static int	color(t_fract *f)
{
	int	color;

	color = ((f->count * 10) << 16 | (f->count * 8) << 5 | (f->count * 1) << 0);
	return (color);
}

// 'Draw_fractal()' function can run either the Mandelbrot set fractal, made
// famous by Benoit Mandelbrot, working for IBM, in 1980, the Tricorn fractal,
// sometimes called the Mandelbar set, as introduced by
// W.D. Crowe, R.Hasson, P.J. Rippon and P.E.D. Strain-Clark, in 1989, as well
// as the Julia set fractal, named after the French mathematician Gaston Julia.
// Defined 'MAX' is the maximum amount of iterations, set to 30.

void	draw_fractal(t_fract *f)
{
	f->y = 1;
	while (f->y <= WINDOW - 1)
	{
		f->x = 1;
		while (f->x <= WINDOW - 1)
		{
			f->c_x = scale(f->x, -2, 2, WINDOW) * f->increment;
			f->c_y = scale(f->y, -2, 2, WINDOW) * f->increment;
			request_adjust(f);
			f->count = 0;
			while ((f->z_x * f->z_x + f->z_y * f->z_y < 4) && (f->count < MAX))
			{
				f->temporary_x = f->z_x * f->z_x - f->z_y * f->z_y + f->c_x;
				f->z_y = f->fractal_toggle * f->z_x * f->z_y + f->c_y;
				f->z_x = f->temporary_x;
				f->count += 1;
			}
			mlx_pixel_put(f->mlx, f->win, f->x, f->y, color(f));
			f->x++;
		}
		f->y++;
	}
}

// 'Launch_fractol()' initializes the 'MLX' library among its controls and
// appoints variables for the fractol sets.
// The mouse motion control, 'motion()', moves the graphical view and calls
// the 'draw_fractal()' function.

int	launch_fractol(t_fract *f)
{
	if (initialize (f) == -1)
		return (-1);
	if (mlx_hook(f->win, 6, 1L << 6, motion, (void *)f) == -1)
		return (-1);
	if (mlx_mouse_hook(f->win, mousepress, f) == -1)
		return (-1);
	if (mlx_key_hook(f->win, keypress, f) == -1)
		return (-1);
	if (mlx_loop(f->mlx) == -1)
		return (-1);
	return (0);
}

// The Main() function checks the amount of arguments sent as parameter
// to the program and in the case of more than one, or if the argument is not
// a number from '1' to '3', prints the usage information.
// Moves on to run the fractal functions afterwards. In case a run time
// error occurs, gives an error message and returns '-1'.

int	main(int argc, char **argv)
{
	const char	*usage[5];
	t_fract		f;

	f.usage_lines = -1;
	if (argc == 2)
		f.request = ft_atoi(argv[1]);
	if (argc != 2 || (f.request != 1 && f.request != 2 && f.request != 3))
	{
		usage[0] = T_OG "Usage: " T_0 "./fractol " T_RED "<command number> \n";
		usage[1] = T_OG "Commands: " T_0;
		usage[2] = T_GREY "<" T_RED "1" T_GREY "> " T_0 "Mandelbrot | ";
		usage[3] = T_GREY "<" T_RED "2" T_GREY "> " T_0 "Julia | ";
		usage[4] = T_GREY "<" T_RED "3" T_GREY "> " T_0 "Tricorn | \n";
		while (++f.usage_lines <= 4)
			write(1, usage[f.usage_lines], ft_strlen(usage[f.usage_lines]));
		return (-1);
	}
	if (launch_fractol(&f) == -1)
	{
		usage[0] = T_RED "ERROR: " T_0 "Launch_fractol() error. Run failure.";
		while (++f.usage_lines <= 0)
			write (1, usage[f.usage_lines], ft_strlen(usage[f.usage_lines]));
		return (-1);
	}
	return (0);
}
