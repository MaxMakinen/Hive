/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:57:49 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/01 12:05:43 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <pthread.h>

# include "mlx.h"
# include "libft.h"
# include "color.h"

# if defined(__linux__)
#  include "linux_keys.h"
# else
#  include "mac_keys.h"
# endif

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 600

typedef void	(*t_funcptr)();

union u_color
{
	int				color;
	unsigned char	rgb[4];
};

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_screen
{
	int	x;
	int	y;
}	t_screen;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mouse
{
	int			pressed;
	t_screen	pos;
}	t_mouse;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	double		multi;
	int			max_iterations;
	int			julia_stop;
	int			mandel;
	int			color;
	int			function;
	t_coord		julia;
	double		scale;
	t_mouse		mouse;
	t_coord		world_min;
	t_coord		world_max;
	t_screen	screen_min;
	t_screen	screen_max;
	t_coord		offset;
	t_coord		zoom;
	t_funcptr	fractal[4];
}	t_data;

void	exit_error(char *str);
int		handle_keypress(int keysym, t_data *data);
void	init_data(t_data *data);
void	create_img(t_data *data, char *name);
void	clean_exit(t_data *data);
void	zero_coord(t_coord *coord);

void	img_pix_put(t_img *img, int x, int y, int color);
int		render(t_data *data);
int		get_color(t_data *data, int iteration);
void	render_background(t_img *img, int color);

void	mandelbrot(t_data *data);
void	julia(t_data *data);
void	multibrot(t_data *data);

void	screen_to_world(t_data *data, t_screen screen, t_coord *world);

void	zoom(t_data *data, double zoom);
void	reset_scale(t_data *data);
void	reset_values(t_data *data);

int		mouse_press(int button, int x, int y, t_data *data);
int		mouse_release(int button, int x, int y, t_data *data);
int		mouse_move(int x, int y, t_data *data);
void	zoom_and_offset(t_data *data, int button);
void	set_scale(t_data *data, t_coord *scale);
void	assign(t_coord *to, t_coord from);
#endif
