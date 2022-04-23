/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:37:58 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/23 15:17:59 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <fcntl.h>

# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# include "fdf.h"
# include "libft.h"

# include <mlx.h>
# ifdef LINUX
	#include <X11/keysym.h>
	#include <X11/X.h>
# endif

# include <stdio.h>

# define MLX_ERROR 1

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

# define OFFSET 23
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0xFF00
# define BLUE_PIXEL 0xFF
# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 0x000000

# define ZOOM 40

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_square
{
	t_vector	p[4];
}	t_square;

typedef struct s_mesh
{
	t_square	*mesh;
	int			len;
}	t_mesh;

typedef struct s_matrix
{
	float	**m;
	float	*pool;
	int		x_max;
	int		y_max;
}	t_matrix;

typedef struct s_coord
{
	int			invisible;
	int			color;
	t_vector	vect;
}   t_coord;

typedef struct s_map
{
	int 		x_max;
	int			y_max;
	float		anglex;
	float		angley;
	float		anglez;
	t_coord		**coords;
	t_coord		*pool;
	t_vector	**vec;
	t_vector	*pvec;
	t_mesh		*grid;
}	t_map;

typedef struct s_img															
{																			   
	void	*mlx_img;														   
	char	*addr;															  
	int		bpp; /* bits per pixel */										   
	int		line_len;														   
	int		endian;															 
	int		origin;
}   t_img;																	  
																				
typedef struct s_data														   
{																			   
	void	*mlx_ptr;														   
	void	*win_ptr;														   
	t_img	img; /* added for image rendering */								
	t_map	map;																
	t_matrix *proj;
}   t_data;																	 
																				
typedef struct s_rect														   
{																			   
	int	x;																	  
	int	y;																	  
	int	width;																  
	int	height;																 
	int	color;																  
}   t_rect;  

t_map		input(char *filename, t_map *map);
void		prep_map(t_map *map);
void		count_elems(char *filename, int *fd, t_map *map);
int			openfd(char *filename, int *fd);
int			closefd(int fd);
t_vector	*prep_vector(t_vector *vector);
t_vector	*vec_mult(t_vector *vect, float num);
t_vector	*vec_add(t_vector *vect, float num);
t_vector	*vec_subt(t_vector *vect, float num);
t_vector	*vec_div(t_vector *vect, float num);
t_matrix	*vec_to_matrix(t_vector *vector, t_matrix *matrix);
t_vector	*matrix_to_vec(t_matrix *matrix, t_vector *vector);
t_matrix	*prep_rotate_z(float angle);
t_matrix	*prep_rotate_x(float angle);
t_matrix	*prep_rotate_y(float angle);
t_matrix	*prep_matrix(int x_max, int y_max);
int			ft_abs(int num);
int			handle_keypress(int keysym, t_data *data);
void		img_pix_put(t_img *img, int x, int y, int color);
void		render_background(t_img *img, int color);
int 		render_rect(t_img *img, t_rect rect);
t_matrix	*mat_mul(t_matrix *matrix, t_matrix *vector);
int			check_color(t_vector coord);
int			render_line(t_img *img, t_vector start, t_vector end);
int			render(t_data *data);
t_map		*project(t_map *map, t_matrix *matrix);
t_matrix	*prep_projection_matrix(void);
t_vector    *mult_matrix_vec(t_vector *src, t_vector *dst, t_matrix *m);
t_square    build_square(t_map *map, t_vector v);
t_mesh  	*make_grid(t_map *map);
void    	draw_grid(t_mesh *grid, t_img *img);
void	    draw_square(t_square sq, t_img *img);
t_vector	*vec_adjust(t_vector *vec, int x, int y);
t_matrix		*isometric(t_map *map, t_img *img, float xoff);
void		log_matrix(t_matrix matrix);
#endif
