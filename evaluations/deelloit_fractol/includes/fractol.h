/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:15:00 by deelliot          #+#    #+#             */
/*   Updated: 2022/09/07 10:44:08 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/includes/libft.h"
# include <mlx.h>
# include <math.h>
# include <pthread.h>

/* pthreads library is needed for multithreading */

/* screen height and width */
# define WIDTH 1280
# define HEIGHT 800

# define USAGE "Usage: ./fractol (julia / mandelbrot / mulitbrot \
/ multijulia / tricorn / burningship / barnsleyfern)"

/* key values */
# define MAX_THREADS 32
# define KEY_DOWN 2
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define UP 13
# define DOWN 1
# define RIGHT 2
# define LEFT 0
# define ESC 53
# define ZOOM_IN 34
# define ZOOM_OUT 31
# define COLOUR 49
# define RESET 36
# define ITER_UP 126
# define ITER_DOWN 125
# define POWER 35

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
}				t_img;

typedef struct s_complex
{
	double	real;
	double	imag;
}				t_complex;

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_win
{
	t_img		img;
	void		*mlx;
	void		*win;
	int			max_iter;
	double		zoom;
	double		x_offset;
	double		y_offset;
	int			fractol_option;
	int			colour;
	t_rgb		col_start;
	t_rgb		col_finish;
	t_range		x_range;
	t_range		width_range;
	t_range		y_range;
	t_range		height_range;
	double		mouse_x;
	double		mouse_y;
	int			lock;
	double		power;
}				t_win;

typedef struct s_thread
{
	int		start;
	int		end;
	t_win	*win;
}				t_thread;

void	handle_errors(t_win	*win);
void	free_win(t_win *win);
void	initialise_window(t_win *win, char *argv);
void	fractal_positions(t_win *win);

/* execute image */
void	execute_image(t_win *win);
void	initialise_image(t_img *img, t_win *win);
void	initialise_colour(t_win *win);
void	initialise_threads(t_win *win);
void	window_menu(t_win *win);

/* draw functions */
void	*plot_points(void *thread_data);
void	img_pixel_put(int n, int x, int y, t_win *win);

/*fractal functions */
int		julia(t_win *win, int x, int y);
int		mandelbrot(t_win *win, int x, int y);
int		multibrot(t_win *win, int x, int y);
int		multijulia(t_win *win, int x, int y);
int		tricorn(t_win *win, int x, int y);
int		burningship(t_win *win, int x, int y);
void	barnsley_fern(t_win *win);

/* handle user input */
int		handle_input(int key, t_win *win);
int		mouse_input(int mouse, int x, int y, t_win *win);
int		mouse_motion(int x, int y, t_win *win);
void	handle_translation(int key, t_win *win);
void	handle_zoom(int key, int x, int y, t_win *win);
void	handle_colour(t_win *win);
void	handle_iterations(int key, t_win *win);
void	handle_power(t_win *win);
void	handle_reset(t_win *win);
void	esc_program(t_win *win);

#endif