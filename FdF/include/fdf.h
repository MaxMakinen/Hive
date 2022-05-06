/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:37:58 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/06 14:34:32 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# include "mlx.h"
# include "libft.h"
# include "error_msg.h"
# if defined(__linux__)
#  include "linux_keys.h"
# else
#  include "mac_keys.h"
# endif
# include "color.h"

# define TRUE 1
# define FALSE 0

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

typedef struct s_vector
{
	float		x;
	float		y;
	float		z;
}	t_vector;

typedef struct s_intvec
{
	int			x;
	int			y;
	int			z;
}	t_intvec;

typedef struct s_draw_tools
{
	t_intvec	delta;
	t_intvec	abs_delta;
	t_intvec	current;
	t_intvec	check;
}	t_d_tools;

typedef struct s_rgb
{
	int			red;
	int			green;
	int			blue;
}	t_rgb;

typedef struct s_matrix
{
	float		**m;
	float		*pool;
	int			x_max;
	int			y_max;
}	t_matrix;

typedef struct s_coord
{
	int			visible;
	t_rgb		color;
	t_vector	vect;
}	t_coord;

typedef struct s_map
{
	int			x_max;
	int			y_max;
	int			z_max;
	int			z_min;
	int			zoom;
	float		f_fov;
	float		f_near;
	float		f_far;
	float		anglex;
	float		angley;
	float		anglez;
	int			rotate;
	float		flatten;
	t_matrix	*proj;
	t_matrix	*rot_x;
	t_matrix	*rot_y;
	t_matrix	*rot_z;
	t_coord		**coords;
	t_coord		*pool;
	t_coord		**vec;
	t_coord		*pvec;
	t_vector	offset;
	t_vector	camera;
}	t_map;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	t_map	*map;
}	t_data;

t_map		*input(char *filename, t_map *map);
void		count_elems(char *filename, int *fd, t_map *map);

void		init_data(t_data *data);
void		create_img(t_data *data, char *name);
void		init_map(t_map *map);
void		center_coords(t_data *data);
void		setup_hooks(t_data *data);

t_vector	*prep_vector(t_vector *vector);
t_vector	*vec_mult(t_vector *vect, float num);
t_vector	*vec_add(t_vector *vect, float num);
void		flatten(t_data *data, int num);
t_vector	*vec_adjust(t_vector *vec, t_vector *offset);
t_vector	*vec_div(t_vector *vect, float num);
t_matrix	*vec_to_matrix(t_vector *vector, t_matrix *matrix);
t_vector	*matrix_to_vec(t_matrix *matrix, t_vector *vector);

t_matrix	*prep_rotate_z(t_matrix *matrix, float angle);
t_matrix	*prep_rotate_x(t_matrix *matrix, float angle);
t_matrix	*prep_rotate_y(t_matrix *matrix, float angle);
int			rotate(t_data *data);

void		pitch(t_data *data, float angle);
void		roll(t_data *data, float angle);
void		yaw(t_data *data, float angle);
void		spin(t_data *data);
void		rot_topleft(t_data *data);
void		rot_topright(t_data *data);
void		rot_bottomleft(t_data *data);
void		rot_bottomright(t_data *data);

void		zoom(t_data *data, int range);
void		rot_flag(t_data *data);
void		set_ortho(t_data *data);
void		set_persp(t_data *data);
void		reset_view(t_data *data);

void		malloc_struct(t_map *map);
void		prep_map(t_map *map);
t_matrix	*prep_matrix(int x_max, int y_max);
t_matrix	*prep_projection_matrix(t_map *map, t_matrix *matrix);

int			ft_abs(int num);
float		ft_lerp(float norm, float min, float max);
float		ft_norm(float num, float min, float max);
int			ft_isnumber(const char *str, int base);
int			ft_isprefix(const char *str, int base);

int			handle_keypress(int keysym, t_data *data);
int			handle_keyrelease(int keysym, t_data *data);

int			mouse_press(int button, int x, int y, t_data *data);
int			mouse_release(int button, int x, int y, t_data *data);
int			mouse_move(int x, int y, t_data *data);

t_matrix	*mat_mul(t_matrix *matrix, t_matrix *vector, t_matrix *result);
t_map		*project(t_map *map, t_matrix *matrix);
t_vector	*mult_matrix_vec(t_vector *src, t_vector *dst, t_matrix *m);

int			render_line(t_img *img, t_coord start, t_coord end);
int			render(t_data *data);
void		img_pix_put(t_img *img, int x, int y, int color);
void		render_background(t_img *img, int color);

int			draw_line(t_data *data, t_coord *start, t_coord *end);
t_intvec	get_current(t_vector *start, t_vector *end, int delta, int dir);
int			in_window(t_intvec *vector);
t_intvec	get_delta(t_vector start, t_vector end);
t_intvec	abs_vector(t_intvec intvec);

t_intvec	find_current(t_vector *strt, t_vector *end, t_d_tools *d_tools);
int			check_color(t_intvec *point, t_coord *start, t_coord *end, \
		t_intvec *delta);
int			rgb_int(t_rgb rgb);
t_rgb		int_rgb(int col);

int			destroy(void *param);
void		free_matrix(t_matrix **matrix);
void		free_coord(t_coord **coord);
void		free_map(t_map **map);
void		clean_exit(t_data *data);

#endif
