/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_uncontrolled_element_of_life.h                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:59:27 by aviholai          #+#    #+#             */
/*   Updated: 2022/10/26 14:24:11 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	``Beautiful, damn hard, increasingly useful. That's fractals.``
//	— Benoit Mandelbrot

#ifndef THE_UNCONTROLLED_ELEMENT_OF_LIFE_H
# define THE_UNCONTROLLED_ELEMENT_OF_LIFE_H

# include <unistd.h>			// UNIX Standard library. ('write()')
# include <stdlib.h>			// Standard library. ('size_t', 'NULL', 'exit')
# include "mlx.h"				// MiniLibraryX graphics library.

// Terminal definitions.
# define MANDELBROT 1			// Reference to running Mandelbrot.
# define JULIA 2				// Reference to running Julia.
# define TRICORN 3				// Reference to running Tricorn.

// Graphic window definitions.
# define WINDOW 860				// Window resolution width

// Mac keyboard and mouse control definitions.
# define MAC_ESC 53					// Mac ESC key.
# define LINUX_ESC 65307			// Linux ESC key.
# define MAC_ZOOM_IN 4				// Mac mouse scroll in.
# define MAC_ZOOM_OUT 5				// Mac mouse scroll out.
# define LINUX_ZOOM_IN 4			// Linux mouse scroll in.
# define LINUX_ZOOM_OUT 5			// Linux mouse scroll out.
# define MAC_CLICK 1				// Mac left click.
# define LINUX_CLICK 1				// Linux left click.

// Terminal output colors.
# define T_GREY "\033[0;37m"	// Grey terminal color.
# define T_OG "\033[1;33m"		// Orange bold terminal color.
# define T_YELL "\033[0;33m"	// Yellow terminal color.
# define T_RED "\033[0;31m"		// Red terminal color.
# define T_0 "\033[0m"			// Default terminal color.

// Graphic window colors.
# define RED 0xCC0000			// Graphic red color.
# define NETTLE 0xAAD4B5		// Graphic "nettles" shade.
# define NIGHT 0x152f37			// Graphic "nightly" shade.
# define DAWN 0x2b6173			// Graphic "twilit" shade.
# define ORANGE 0xE7C9B1		// Graphic orange color.
# define WHITE 0xdbdbdb			// Not-quite-white white shade.
# define GREY 0x828282			// Graphic grey color.

typedef struct s_fract {
	int		request;
	int		usage_lines;
	void	*mlx;
	void	*win;
	float	x_side;
	float	y_side;
	float	left;
	float	top;
	float	increment;
	float	x_scale;
	float	y_scale;
	float	z_x;
	float	z_y;
	float	c_x;
	float	c_y;
	float	temporary_x;
	int		x;
	int		y;
	int		count;
	int		fractal_toggle;
	float	mouse_x;
	float	mouse_y;
}	t_fract;

int		main(int argc, char **argv);	// Main function.
int		launch_fractol(t_fract *f);		// Runs the request to graphic view.
int		initialize(t_fract *f);			// Sets graphic and necessary variables.
void	draw_fractal(t_fract *f);		// Draws the fractal requested.
void	write_strings(t_fract *f);		// Writes tool tips on the window.
int		keypress(int key, void *param);	// Graphic window keyboard controls.
int		mousepress(int key, int x, int y, void *param);	// Mouse zoom control.
int		motion(int x, int y, void *param);				// Mouse motion control.
float	scale(int value, float n_min, float n_max, float o_max); // Normalize.
size_t	ft_strlen(const char *s);		// Measures applied string length.
int		ft_atoi(const char *str);		// 'AtoI', ASCII to integer converter.
#endif
