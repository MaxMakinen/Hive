/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:54:47 by dpalacio          #+#    #+#             */
/*   Updated: 2022/04/28 16:07:10 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>

/*----RESOLUTION----*/
# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080

/*------COLORS------*/
# define WHITE		0xFFFFFF
# define RED		0xFF0000
# define GREEN		0x00FF00
# define BLUE		0x0000FF
# define YELLOW		0xFFFF00
# define CYAN		0x00FFFF
# define MAGENTA	0xFF00FF

/*-------DATA-------*/
typedef struct s_data{
	void	*mlx;
	void	*win;
	void	*img;
	int		px_bits;
	int		line_bytes;
	int		endian;
	char	*img_addr;
	int		map_width;
	int		map_height;
	float	**matrix;
	int		**color_matrix;
	int		color_scheme;
	int		zoom;
	int		x_off;
	int		y_off;
	float	iso_angle;
	float	rot_angle;
	int		view;
}				t_data;

/*-------LINE------*/
typedef struct s_line{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}				t_line;

/*-------MAIN-------*/
void	error_print(char *e_string, t_data *data);

/*-----READ FILE----*/
void	read_file(char *file, t_data *data);

/*----UI DISPLAY----*/
void	display_controls(t_data *data);
void	draw_ui(t_data *data);
void	display_info(t_data *data);

/*-----CONTROLS-----*/
void	controls(t_data *data);
int		on_keydown(int key, t_data *data);
int		on_keyup(int key, t_data *data);
int		on_mousedown(int key, int x, int y, t_data *data);
int		auto_rot(t_data *data);

/*-MOUSE CONTROLLER-*/
int		mouse_wheel(int button, int x, int y, t_data *data);
int		right_click(int key, int x, int y, t_data *data);

/*--KEY CONTROLLER--*/
int		exit_fdf(int key, t_data *data);
int		pan_view(int key, t_data *data);
int		switch_view(int key, t_data *data);
int		change_height(int key, t_data *data);
int		change_angle(int key, t_data *data);

/*---DRAW MANAGER---*/
void	offset_draw(t_data *data);
int		draw_line(t_line line, t_data *data, int color0, int color1);
void	img_pixel_put(t_data *data, int x, int y, int color);
void	draw(t_data *data);
t_line	make_line(t_data *data, char *dir, int x, int y);

/*-----DRAW MAP-----*/
void	draw_map(t_data *data);
void	rotate(int *x, int *y, t_data *data);
void	isometric(int *x, int *y, int z, t_data *data);

/*---COLOR MANAGER--*/
void	choose_color(t_data *data, int x, int y);

/*--COLOR GRADIENT--*/
int		color_gradient(int c0, int c1, int steps);

/*-COLOR CONVERSION-*/
int		rgb_to_int(int red, int blue, int green);
int		int_to_red(int color);
int		int_to_green(int color);
int		int_to_blue(int color);

#endif
