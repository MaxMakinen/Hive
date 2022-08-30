/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:08:33 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/26 15:14:13 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

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
# define BIAS 1e-4

typedef int	(*t_funcptr)();

typedef union u_rgb
{
	unsigned int	color;
	unsigned char	rgb[4];
}	t_rgb;

enum e_type
{
	sphere,
	plane,
	cylinder,
	cone
};

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

typedef	struct s_vec4f
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4f;

typedef	struct s_mat44f
{
	t_vec4f up;
	t_vec4f right;
	t_vec4f forward;
	t_vec4f translate;
}	t_mat44f;

typedef struct s_obj
{
	char			*name;
	enum e_type		type;
	t_vec3f			position;
	t_vec3f			normal;
	t_rgb			color;
	float			radius;
	float			radius2;
	float			height;
	struct s_obj	*next;
}	t_obj;

typedef struct s_object
{
	t_vec3f	sphere_pos;
	t_vec3f	cylinder_pos;
	t_vec3f	plane_orig;
	t_vec3f	cone_pos;
	t_vec3f	plane_normal;
	t_vec3f	cylinder_normal;
	t_vec3f	cone_normal;
	t_rgb	sphere;
	t_rgb	plane;
	t_rgb	cylinder;
	t_rgb	cone;
	int		type;
	float	radius;
	float	radius2;
	float	cylinder_radius;
	float	cylinder_radius2;
	float	cone_radius;
	float	cone_radius2;
	float	cone_height;
}	t_object;

typedef	struct s_camera
{
	t_vec3f	pos;
	t_vec3f	dir;
}	t_camera;

typedef	struct s_light
{
	t_vec3f	pos;
	t_rgb	color;
	float	brightness;
}	t_light;

typedef	struct s_scene
{
	char		*name;
	t_camera	camera;
	t_mat44f	camera_to_world;
	t_light		*light;
	t_object	object;
	t_obj		*obj;
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

int	sphere_intersect(t_scene *scene, t_vec3f origin, t_vec3f direction, float radius2, float *t0);
int	plane_intersect(t_scene *scene, t_vec3f origin, t_vec3f direction, t_vec3f normal, float *intersect);

t_vec3f	vec_mult(t_vec3f vec1, float mult);
t_vec3f	vec_minus(t_vec3f vec1, t_vec3f vec2);
t_vec3f	vec_plus(t_vec3f vec1, t_vec3f vec2);
float	get_angle(t_vec3f vec1, t_vec3f vec2);
t_vec3f	cross_product(t_vec3f vec1, t_vec3f vec2);
t_vec3f	normalize(t_vec3f vec);
double	vec_len(t_vec3f vec);
double	dot_product(t_vec3f vec1, t_vec3f vec2);

void	angle_color(t_data *data, t_scene *scene, t_vec3f intersection, int x, int y, t_rgb color, t_vec3f normal);
void	norm_color(t_data *data, t_scene *scene, t_vec3f hit_pos, int x, int y);
void	norm_dot_color(t_data *data, t_scene *scene, t_vec3f hit_pos, int x, int y, t_rgb color, t_vec3f normal);

#endif
