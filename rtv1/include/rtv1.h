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

# include "vector.h"
# include "quaternion.h"

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
# define VFOV 90

typedef int	(*t_funcptr)();

typedef union u_rgb
{
	unsigned int	color;
	unsigned char	rgb[4];
}	t_rgb;

enum e_type
{
	e_none,
	e_camera,
	e_light,
	e_sphere,
	e_plane,
	e_cylinder,
	e_cone
};

typedef struct s_ray
{
	t_vec3f	orig;
	t_vec3f	dir;
}	t_ray;

typedef	struct s_map
{
	int	*pool;
	int	**ptr;
}	t_map;

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
	double			vfov;
	t_vec3f			pos;
	t_vec3f			dir;
	t_vec3f			up;
	t_vec3f			right;
	t_rgb			color;
	double			radius;
	double			radius2;
	double			height;
	double			brightness;
	struct s_obj	*next;
}	t_obj;

typedef	struct s_scene
{
	char		*name;
	t_mat44f	camera_to_world;
	t_vec3f		horizontal;
	t_vec3f		vertical;
	t_vec3f		lower_left;
	double		view_height;
	double		view_width;
	t_obj		*obj;
	t_obj		*light;
	t_obj		*cam;
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
	void	*mlx_ptr;
	void	*win_ptr;
	t_vec3i	screen_min;
	t_vec3i	screen_max;
	double	aspect_ratio;
	t_img	*img;
	t_map	map;
}	t_data;

typedef struct s_pattern
{
	double	width;
	double	height;
	t_rgb	color1;
	t_rgb	color2;
}	t_pattern;

typedef struct	s_hit
{
	t_vec3f	pos;
	t_vec3f	normal;
	t_vec2f	surface;
	t_vec3f	rotated;
	t_obj	*obj;
	t_rgb	color;
	t_vec3f	color3;
}	t_hit;

void	render_scene(t_scene *scene, t_data *data);

void	make_image(t_scene *scene, t_data *data);
void	exit_error(char *str);
void	init_data(t_data *data, t_scene *scene);

int		open_file(int *fd, const char *filename);
int	close_file(int fd);

void	render_background(t_img *img, int color);
void	create_img(t_data *data, char *name);
void	img_pix_put(t_img *img, int x, int y, int color);

int	handle_keypress(int keysym, t_data *data);
int	render(t_data *data);

void	clean_exit(t_data *data);

int	sphere_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1);
int	cylinder_intersect(t_ray *ray, t_obj *object, double *t0, double *t1);
int	cone_intersect(t_ray *ray, t_obj *object, double *t0, double *t1);
int	plane_intersect(t_ray *ray, t_obj *object, double *t0, double *t1);

t_rgb	color_mult(t_rgb color, double num);

t_vec2f	get_spherical(t_obj *obj, t_vec3f rotated);
t_vec2f	get_planar(t_vec3f rotated);
t_vec2f	get_cylindrical(t_vec3f rotated);

t_hit	*get_normal(t_obj *object, t_hit *hit, t_ray *ray);
void	rotate(t_obj *object, t_hit *hit);
double	deg_to_rad(double deg);


double	get_angle(t_vec3f vec1, t_vec3f vec2);
int		quadratic_formula(double a, double b, double c, double *t0, double *t1);

int		norm_dot_color(t_data *data, t_vec3f *light, t_hit *hit);

int		read_input(t_scene *scene, const char *file_name);

int		ft_bit(int step);
double  ft_clamp(double num, double min, double max);
void	ft_swapf(double *a, double *b);
double	ft_atod(char *str);

t_obj	*init_object(t_scene *scene);

int		ft_floor(double num);
t_obj	*get_obj(t_obj* head, enum e_type type);
int		shade_ray(t_scene *scene, t_ray *ray, t_hit *hit, t_rgb *color);
t_vec3f	get_intersect(t_vec3f origin, t_vec3f direction, double distance);
void	print_vec(t_vec3f *vec);

//input
char	*str_insert(char *str);
t_obj	*get_last(t_obj *head);
t_obj	*init_obj(void);
int		get_vector(t_vec3f *vector, char **words);

//ray utils
t_vec3f	get_intersect(t_vec3f origin, t_vec3f direction, double distance);
int	check_intersect(t_obj *obj, t_ray *ray, double *temp, double *t1);
t_vec3f	get_direction(t_data *data, double x, double y, t_scene *scene);
t_obj *get_obj(t_obj* head, enum e_type type);

#endif