/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:31:29 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 14:53:31 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# define SCREEN_X 2560
# define SCREEN_Y 1440
# define PI 3.141592

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		max_x;
	int		max_y;
}				t_img;

typedef struct s_proj
{
	float	z_near;
	float	z_far;
	float	fov;
	float	asp_ratio;
	float	fov_rad;
}				t_proj;

typedef struct s_rot
{
	float	alpha;
	float	beta;
	float	gamma;
}				t_rot;

typedef struct s_cols
{
	int	r;
	int	g;
	int	b;
}				t_cols;

typedef struct s_sliders
{
	int		fov;
	int		red;
	int		blue;
	int		green;
	int		elev;
}				t_sliders;

typedef struct s_mat
{
	float	m[4][4];
}				t_mat;

typedef struct s_utils
{
	void		*mlx;
	void		*win;
	int			**map;
	int			color;
	int			color_top;
	int			mix_color;
	int			dest_color;
	int			lines;
	int			h_point;
	int			l_point;
	int			map_h;
	int			longest_line;
	int			clock;
	int			scale;
	int			perspective;
	int			state;
	int			reference;
	int			screen_x;
	int			screen_y;
	int			mouse_x;
	int			mouse_y;
	int			move_x;
	int			move_y;
	int			map_x;
	int			map_y;
	int			map_color;
	t_sliders	slid;
	t_rot		rot;
	t_mat		pmatrix;
	t_mat		rmatrix_x;
	t_mat		rmatrix_y;
	t_mat		rmatrix_z;
	t_proj		proj;
	t_img		img;
	t_img		img2;
	t_img		*draw_img;
}				t_utils;

typedef struct s_3d
{
	float	x;
	float	y;
	float	z;
}				t_3d;

typedef struct s_2d
{
	int	a;
	int	b;
}				t_2d;

typedef struct s_line
{
	int	x;
	int	y;
	int	x_dest;
	int	y_dest;
}				t_line;

typedef struct s_quadril
{
	int	a;
	int	b;
	int	c;
	int	d;
	int	e;
	int	f;
	int	g;
	int	h;
}				t_quadril;

/*Fdf functions*/
void	close_fdf(t_utils *utils, char *exit_msg, int exit_code);
t_3d	draw_map(t_utils *utils, int x, int y, int z);
void	draw_sliders(t_utils *utils);
void	iter_coords(t_utils *utils);
/*Coloring functions*/
int		combine_channels(int red, int green, int blue);
void	seperate_channels(int color, int *red, int *green, int *blue);
int		mix_colors(int color, int color2, float percent);
void	get_color_mix(t_utils *utils);
/*Drawing functions*/
void	draw_n_line(t_utils *utils, t_line *line, int len, int color);
void	draw_line(t_utils *utils, t_line *line, int color, int dest_color);
void	ft_clear_img(t_utils *utils);
void	ft_pixel_put(t_utils *utils, int x, int y, int color);
void	draw_quadrilateral(t_utils *utils, t_quadril *xy, int color);
void	draw_square(t_utils *utils, t_line *l, int color);
void	render_screen(t_utils *utils);
/*Hook functions*/
int		clock(void *param);
/*Mouse functions*/
int		mouse_move(int x, int y, void *param);
int		mouse_up(int button, int x, int y, void *param);
int		mouse_down(int button, int x, int y, void *param);
/*Keyboard functions*/
int		key_down(int keycode, void *param);
/*Process file functions*/
void	get_map(int fd, t_utils *utils);
int		count_lines(int fd);
/*Useful functions*/
void	print_map(t_utils *utils);
/*Init functions*/
void	init(t_utils *utils);
void	init_hooks(t_utils *utils);
void	init_matrix(t_mat *matrix);
void	init_pmatrix(t_utils *utils);
void	init_rmatrix_x(t_utils *utils);
void	init_rmatrix_z(t_utils *utils);
void	init_rmatrix_y(t_utils *utils);
void	init_proj(t_utils *utils);
/*Transformation functions*/
void	matrix_multip(t_3d *in, t_3d *out, t_mat *matrix);
void	scale_into_view(t_utils *utils, float *x, float *y);
void	scale_depth(t_utils *utils, float *z);
/*Help functions*/
int		int_to_bit(int nbr);
void	rot_overflows(t_utils *utils);

#endif
