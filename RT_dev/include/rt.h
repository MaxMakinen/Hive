/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:01:57 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/15 15:14:45 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../build/libsdl2/include/SDL2/SDL.h"
# include "../libft/libft.h"
# include "multi_thread.h"
# include "object.h"
# include "vector.h"
# include <fcntl.h>
# include <math.h>
# include "../build/libsdl2/include/SDL2/SDL.h"
# include "vector.h"
# include "object.h"
# include "multi_thread.h"
# include "perlin_noice.h"
# include "patterns.h"
# include "motion.h"
# include <stdio.h>

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# define WIN_W 42
# define WIN_H 42
# define MAX_DISTANCE 9999
# define A_A_DIV 6
# define EPSILON 0.00006103515625

enum
{
	STEREOSCOPY,
	NORMAL,
	BLACK_AND_WHITE,
	SEPIA,
	CARTOON,
	B_W_CARTOON,
	EDGE,
};

typedef struct s_frame_buffer
{
	int				*data;
	int				*filter;
	int				*stereocopy;
	char			*mask;
	t_color			*motion_calc;
	int				data_len;
}					t_frame_buffer;

typedef struct s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		event;
	SDL_Texture		*texture;
	t_frame_buffer	frame_buffer;
	int				stereocopy;
}					t_sdl;

typedef struct s_cam
{
	t_point			pos;
	t_tuple			v_up;
	t_point			coi;
	t_tuple			v;
	t_tuple			u;
	t_tuple			n;
	t_tuple			c;
	t_tuple			l;
	t_matrix 		transform;
	t_matrix 		coi_transform;
	double			plane_h;
	double			plane_w;
	t_motion_blur	motion;
	t_motion_blur	coi_motion;
}					t_cam;

typedef struct s_screen_shot
{
	FILE			*fp;
	int				fd;
}					t_screen_shot;

typedef struct s_scene
{
	t_vec			lights;
	t_vec			objects;
	t_cam			cam;
}					t_scene;

typedef struct s_main
{
	t_sdl			sdl;
	t_cam			cam;
	t_multi			multi;
	t_ray			ray;
	t_ray			shadow;
	t_light			light;
	t_perlin		perlin;
	t_object		obj[500];
	int				obj_count;
	int				shape_count;
	int				ant_al;
	t_scene			scene;
}					t_main;

int					initialize_window(t_main *main);
void				initialize_camera(t_cam *cam, t_matrix transform);
t_matrix			coi_transform(t_cam *cam, t_matrix transform);
void				initialize_ray(t_ray *ray, double x, double y, t_cam *cam);
void				render_image(t_main *main, int task, int ant_al);

double				intersects_cone(t_ray *ray, t_object *cone);
double				intersects_cylinder(t_ray *ray, t_object *cylinder);
double				intersects_plane(t_ray *ray, t_object *plane);
double				intersects_sphere(t_ray *ray, t_object *sphere);

double				calc_b2_4ac(t_abc abc);
double				quadratic(t_abc abc, double b2_4ac);

t_vec3				vec3_ray_at(t_ray u, double x);

int				get_shape_intersections(t_ray *ray, t_object *shape);

t_tuple				get_cylinder_normal(t_main *main, t_hit_record *hit);
t_tuple				get_sphere_normal(t_main *main, t_hit_record *hit);
t_tuple				get_cone_normal(t_main *main, t_hit_record *hit);

void				add_hit_color(t_main *main, t_ray *shadow);
unsigned int		color_to_int(t_color color);
void				fix_aliasing_color(t_main *main, int sub_pixel_count);
int					check_shadow(t_main *main, t_ray *ray);
void				creat_filters(t_frame_buffer *fb, int filter_type);
void				create_sepia(t_frame_buffer *fb);
void				create_stereoscope(t_main *main, t_matrix cam_scale, t_matrix cam_transform);


int					rgb_to_white(t_color *rgb);
void				int_to_rgb(int color, t_color *rgb);
void				edge_detection(t_frame_buffer *fb);

int					draw_frame(t_main *main);
void				worker_wait(t_main *ctx);
void				worker_task(int *task_n, t_main *ctx);
void				worker_broadcast(t_main *ctx);

void				draw_to_window(t_sdl *sdl, int *filter);
void				draw_filter(t_sdl *sdl, int *filter_type, int i);
void				kay_hooks(t_sdl *sdl, int *quit, int *filter_type);
void				creat_screen_shot(int *image);
char				*create_screen_shot_name(char *image_name, int image_nbr);

void				*taskhandler(void *main);
void				create_threads(t_main *main, int ant_al);
void				init_pthread(t_main *main);
double				fabs(double x);
int					int_clamp(int value, int min, int max);
double				float_clamp(double value, double min, double max);

t_point				ray_position(t_ray ray, double t);



t_light				point_light_new(t_point position, t_color intensity);
t_light				sun_light_new(t_point direction, t_color intensity);
/* t_light				ambient_light_new(t_color intensity); */
t_material			material_new();


t_color				lighting(t_material *mat,  t_light light, t_point point,t_vector to_eye, t_vector normal, int in_shadow);
void				img_pixel_put(
						t_frame_buffer *fb, 
						unsigned int x,
						unsigned int y, t_color color);

int					scene_new(t_scene *scene);
int					default_scene(t_scene *scene);
void		scene_intersect(t_scene *scene, t_ray *ray);


void	pattern_at(t_hit_record hit,t_point hit_loc, t_color *hit_color, t_perlin *perlin);

int		motion_set_all(t_main *main);
void	create_motion_blur(t_main *main);
t_color	reflected_color(t_scene *scene, t_ray *ray);
int		is_shadowed(t_scene *scene, t_light light, t_point point);
t_color	color_at(t_scene *scene, t_ray *ray);
int		fill_hit_record(t_main *main, t_ray *ray);
int		find_next_intersection(t_ray *ray, t_intersection *closest_t,
							t_negative *neg_hits, t_scene *scene);
t_intersection	find_negative_object_intersect(t_ray *ray, int neg_obj_id,
												t_scene *scene);
int				precompute(t_ray *ray, t_scene *scene);
t_color			shade_hit(t_scene *scene, t_ray *ray);
#endif
