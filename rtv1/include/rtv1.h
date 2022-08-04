/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:08:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/04 22:51:42 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

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

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 800
# define TRUE 1
# define FALSE 0

typedef union u_rgb
{
	unsigned int	color;
	unsigned char	rgb[4];
}	t_rgb;

typedef	struct s_map
{
	int	*pool;
	int	**ptr;
}	t_map;

typedef	struct s_ivec
{
	int	x;
	int	y;
	int	z;
}	t_ivec;

typedef	struct s_3vec
{
	float	x;
	float	y;
	float	z;
}	t_3vec;

typedef struct s_object
{
	t_3vec	position;
	t_3vec	origin;
	t_3vec	normal;
	t_rgb	color;
	t_rgb	plane;
	int		type;
	float	radius;
	float	radius2;
}	t_object;

typedef	struct s_scene
{
	t_3vec		camera;
	t_ivec		screen_min;
	t_ivec		screen_max;
	t_3vec		light;
	t_object	object;
	int			max_objects;
}	t_scene;

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
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	t_map		map;
}	t_data;

void	make_image(t_scene *scene, t_data *data);
void	exit_error(char *str);
void	init_data(t_data *data, t_scene *scene);

void	render_background(t_img *img, int color);
void	create_img(t_data *data, char *name);
void	img_pix_put(t_img *img, int x, int y, int color);

int	handle_keypress(int keysym, t_data *data);
int	render(t_data *data);

void	clean_exit(t_data *data);

#endif
