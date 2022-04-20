/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:37:58 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/20 13:50:02 by mmakinen         ###   ########.fr       */
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
	int	x;
	int	y;
	int	z;
	int	w;
}	t_vector;

typedef struct s_matrix
{
	int **matrix;
	int	*pool;
}	t_matrix;

typedef struct s_coord
{
	int			invisible;
	int			color;
	t_vector	vect;
}   t_coord;

typedef struct s_map
{
	int 	x_max;
	int		y_max;
	t_coord	**coords;
	t_coord	*pool;
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
}   t_data;																	 
																				
typedef struct s_rect														   
{																			   
	int	x;																	  
	int	y;																	  
	int	width;																  
	int	height;																 
	int	color;																  
}   t_rect;  

t_map	input(char *filename, t_map *map);
void	prep_map(t_map *map);
void	count_elems(char *filename, int *fd, t_map *map);
int		openfd(char *filename, int *fd);
int		closefd(int fd);
t_vector	*prep_vector(t_vector *vector);
t_vector vect_mult(t_vector vect, int num);
t_vector *vect_add(t_vector *vect, int num);
t_vector *vect_subt(t_vector *vect, int num);
t_vector *vect_div(t_vector *vect, int num);
t_matrix *vec_to_matrix(t_vector *vector);
t_vector	*matrix_to_vec(t_matrix *matrix);
t_matrix	*rotate_z(int angle);
t_matrix	*rotate_x(int angle);
t_matrix	*rotate_y(int angle);
t_matrix	*prep_matrix(t_matrix *matrix);
int	ft_abs(int num);
int handle_keypress(int keysym, t_data *data);
void img_pix_put(t_img *img, int x, int y, int color);
void render_background(t_img *img, int color);
int render_rect(t_img *img, t_rect rect);
t_matrix	*mat_mul(t_matrix *matrix, t_matrix *vector);
int	check_color(t_vector coord);
int	render_line(t_img *img, t_vector start, t_vector end);
int render(t_data *data);
#endif
