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
# define ALBEDO 0.05729577951
# define GAMMA 2.2
# define EPSILON 2.220446e-15

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
	e_cone,
	e_disc,
	e_box,
	e_triangle
};

typedef struct s_ray
{
	t_vec3f	orig;
	t_vec3f	dir;
	t_vec3f	inv_dir;
}	t_ray;

typedef struct s_map
{
	int	*pool;
	int	**ptr;
}	t_map;

typedef struct s_obj
{
	enum e_type		type;
	double			vfov;
	t_vec3f			pos;
	t_vec3f			dir;
	t_vec3f			up;
	t_vec3f			right;
	t_vec3f			col;
	t_vec3f			bb_min;
	t_vec3f			bb_max;
	t_vec3f			vertex0;
	t_vec3f			vertex1;
	t_vec3f			vertex2;
	t_rgb			color;
	double			radius;
	double			radius2;
	double			height;
	double			brightness;
	int				pattern;
	int				shiny;
	double			n;
	double			kd;
	double			ks;
	struct s_obj	*next;
}	t_obj;

typedef struct s_scene
{
	char		*name;
	t_vec3f		horizontal;
	t_vec3f		vertical;
	t_vec3f		lower_left;
	double		view_height;
	double		view_width;
	t_obj		*obj;
	t_obj		*light;
	t_obj		*cam;
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
	t_scene	*scene;
}	t_data;

typedef struct s_hit
{
	t_vec3f	pos;
	t_vec3f	normal;
	t_vec2f	surface;
	t_vec3f	rotated;
	t_ray	*ray;
	t_obj	*obj;
	t_rgb	color;
	double	dist;
}	t_hit;

void	exit_error(char *str);
int		open_file(int *fd, const char *filename);
int		close_file(int fd);
int		read_input(t_data *data, const char *file_name);
t_obj	*init_obj(t_data *data);

void	init_data(t_data *data, t_scene *scene);
void	render_scene(t_scene *scene, t_data *data);
void	make_image(t_scene *scene, t_data *data);
void	create_img(t_data *data, char *name);

void	render_background(t_img *img, int color);
void	img_pix_put(t_img *img, int x, int y, int color);
int		handle_keypress(int keysym, t_data *data);
int		render(t_data *data);

void	clean_exit(t_data *data);
void	free_objects(t_scene *scene);

int		sphere_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1);
int		cylinder_intersect(t_ray *ray, t_obj *object, double *t0, double *t1);
int		cone_intersect(t_ray *ray, t_obj *object, double *t0, double *t1);
int		plane_intersect(t_ray *ray, t_obj *object, double *t0, double *t1);
int		disc_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1);
int		aabb_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1);
int		triangle_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1);

t_vec2f	get_spherical(t_obj *obj, t_vec3f rotated);
t_vec2f	get_planar(t_vec3f rotated);
t_vec2f	get_cylindrical(t_vec3f rotated);

void	get_normal(t_obj *object, t_hit *hit, t_ray *ray);
void	rotate(t_obj *object, t_hit *hit);
double	deg_to_rad(double deg);

double	get_angle(t_vec3f vec1, t_vec3f vec2);
int		quadratic_formula(double *input, double *t0, double *t1);

int		ft_bit(int step);
double	ft_clamp(double num, double min, double max);
void	ft_swapf(double *a, double *b);
double	ft_atod(char *str);
int		ft_floor(double num);

t_obj	*get_obj(t_obj *head, enum e_type type);

void	cast_ray(t_ray *ray, t_scene *scene, t_hit *hit);
int		shade_ray(t_scene *scene, t_hit *hit, t_obj *light);
t_vec3f	gamma_correct(t_vec3f color);
t_vec3f	get_pattern(t_hit *hit);

t_vec3f	get_intersect(t_vec3f origin, t_vec3f direction, double distance);
void	print_vec(t_vec3f *vec);

/*input*/
char	*str_insert(char *str);
t_obj	*get_last(t_obj *head);
t_vec3f	get_vector(t_vec3f vector, char **words);
void	get_description(t_obj *temp, char **words);
t_vec3f	rotation(t_obj *temp, char **words);

/*ray utils*/
t_vec3f	get_intersect(t_vec3f origin, t_vec3f direction, double distance);
int		check_intersect(t_obj *obj, t_ray *ray, t_hit *hit);
t_vec3f	get_direction(t_data *data, double x, double y, t_scene *scene);
t_obj	*get_obj(t_obj *head, enum e_type type);
void	prep_round(t_hit *hit, t_obj **object, t_scene *scene);

double	ft_max(const double num1, const double num2);
double	ft_min(const double num1, const double num2);

#endif