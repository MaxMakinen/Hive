/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:57:49 by mmakinen          #+#    #+#             */
/*   Updated: 2022/07/13 09:40:09 by mmakinen         ###   ########.fr       */
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

# include "mlx.h"
# include "libft.h"
# include "color.h"

# if defined(__linux__)
#  include "linux_keys.h"
# else
#  include "mac_keys.h"
# endif

# define TRUE 1
# define FALSE 0

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900

# define KEY_ESC 65307

union u_color
{
	int	color;
	char rgb[4];
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
	int			max_iterations;
	t_coord		zoom;
	t_mouse		mouse;
	t_coord		world_min;
	t_coord		world_max;
	t_screen	screen_min;
	t_screen	screen_max;
	t_coord		offset;
	t_coord		scale;
}	t_data;

void	exit_error(char *str);
int		handle_keypress(int keysym, t_data *data);
void	init_data(t_data *data);
void	create_img(t_data *data, char *name);
void	clean_exit(t_data *data);

void	img_pix_put(t_img *img, int x, int y, int color);
int		render(t_data *data);
int		get_color(t_data *data, int iteration);

void	mandelbrot(t_data *data);
void	julia(t_data *data);

void	world_to_screen(t_data *data, t_coord world, t_screen *screen);
void	screen_to_world(t_data *data, t_screen screen, t_coord *world);

void	zoom(t_data *data, double zoom);
void	reset_scale(t_data *data);
void	reset_values(t_data *data);

int mouse_press(int button, int x, int y, t_data *data);
int	mouse_release(int button, int x, int y, t_data *data);
int	mouse_move(int x, int y, t_data *data);
#endif
