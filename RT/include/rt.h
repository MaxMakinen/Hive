/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:01:57 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/20 18:57:14 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../build/libsdl2/include/SDL2/SDL.h"
# include "libft.h"
# include "vector.h"
# include "object.h"
# include "multi_thread.h"

# define WIN_W 1920
# define WIN_H 1080
# define A_A_DIV 6

typedef struct s_frame_buffer
{
	int			*data;
	int			*cartoon;
	int			*b_w;
	int			*b_w_cartoon;
	int			*edge_map;
	char		*mask;
	int			data_len;
}				t_frame_buffer;

typedef struct s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		event;
	SDL_Texture		*texture;
	t_frame_buffer	frame_buffer;
}				t_sdl;

typedef struct s_cam
{
	t_vec3	pos;
	t_vec3	v_up;
	t_vec3	coi;
	t_vec3	v;
	t_vec3	u;
	t_vec3	n;
	t_vec3	c;
	t_vec3	l;
	double	plane_h;
	double	plane_w;
}			t_cam;

typedef struct s_hit_record
{
	t_vec3	hit_loc;
	t_vec3	normal;
	double	hit_dist;
	int		clo_obj_id;
	union u_tuple	color;
}				t_hit_record;

typedef struct s_ray
{
	t_vec3		orig;
	t_vec3		dir;
	t_hit_record	hit;
}				t_ray;

typedef struct s_light
{
	t_vec3		pos;
}				t_light;

typedef struct s_main
{
	t_sdl		sdl;
	t_cam		cam;
	t_multi		multi;
	t_ray		ray;
	t_ray		shadow;
	
	t_light		light;
	t_object	obj[10];
	int			obj_count;
	int			shape_count;
	int			ant_al;
}				t_main;

void	*ft_memcpy(void *dst, const void *src, size_t n);


int		initialize_window(t_main *main);
void	initialize_camera(t_cam *cam);
void	initialize_ray(t_ray *ray, double x, double y, t_cam *cam);
void	render_image(t_main	*main, int task, int ant_al);

double	intersects_cone(t_ray *ray, t_object *cone);
double	intersects_cylinder(t_ray *ray, t_object *cylinder);
double	intersects_plane(t_ray *ray, t_object *plane);
double	intersects_sphere(t_ray *ray, t_object *sphere);

double	calc_b2_4ac(t_abc abc);
double	quadratic(t_abc abc, double b2_4ac);

t_vec3	vec3_ray_at(t_ray u, double x);

double	get_shape_intersections(t_ray *ray, t_object *shape);

t_vec3	get_cylinder_normal(t_main *main, t_hit_record *hit);
t_vec3	get_sphere_normal(t_main *main, t_hit_record *hit);
t_vec3	get_cone_normal(t_main *main, t_hit_record *hit);

void			add_hit_color(t_main *main, t_ray *shadow);
unsigned int	color_to_int(t_color color);
void			fix_aliasing_color(t_main *main, int sub_pixel_count);
int				check_shadow(t_main *main, t_ray *ray);
void	creat_filters(t_frame_buffer * fb);

int		rgb_to_white(t_color *rgb);
void	int_to_rgb(int color, t_color *rgb);
void	edge_detection(t_frame_buffer *fb);

int		draw_frame(t_main *main);
void	*taskhandler(void *main);
void	create_threads(t_main *main, int ant_al);
void	init_pthread(t_main *main);
#endif