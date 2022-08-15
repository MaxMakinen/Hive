/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:08:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/12 16:53:09 by mmakinen         ###   ########.fr       */
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

typedef int	(*t_funcptr)();

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

typedef	struct s_vec3i
{
	int	x;
	int	y;
	int	z;
}	t_vec3i;

typedef	struct s_vec3f
{
	float	x;
	float	y;
	float	z;
}	t_vec3f;

typedef struct s_obj
{
	t_vec3f		position;
	t_vec3f		normal;
	t_rgb		color;
	t_funcptr	func;
	float		radius;
	float		radius2;
	struct s_obj		*next;
}	t_obj;

typedef struct s_object
{
	t_vec3f	sphere_pos;
	t_vec3f	cylinder_pos;
	t_vec3f	plane_orig;
	t_vec3f	plane_normal;
	t_rgb	sphere;
	t_rgb	plane;
	int		type;
	float	radius;
	float	radius2;
	float	cylinder_radius;
	float	cylinder_radius2;
}	t_object;

typedef	struct s_scene
{
	t_vec3f		camera;
	t_vec3f		light;
	t_vec3f		light_dir;
	t_object	object;
	t_obj		*head;
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
	t_vec3i		screen_min;
	t_vec3i		screen_max;
	float		aspect_ratio;
	float		fov;
	float		scale;
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

int	sphere_intersect(t_scene *scene, t_vec3f direction, t_object *object, float *t0);
int	plane_intersect(t_scene *scene, t_vec3f direction, t_object *object, float *intersect);

#endif
