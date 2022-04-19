/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:37:58 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/19 12:41:22 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

# include <stdio.h>

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
	int		 bpp; /* bits per pixel */										   
	int		 line_len;														   
	int		 endian;															 
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
#endif
