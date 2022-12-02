/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:56:24 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/28 15:06:12 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "../libft/libft.h"
# include "matrix.h"
# include "tuple.h"
# include "vector.h"
# include "patterns.h"
# include <stdlib.h>

enum e_object
{
	SPHERE,
	CYLINDER,
	PLANE,
	CONE,
	SUN,
	POINT,
};

// For ambient, diffuse, and specular, the typical values are between 0 and 1. 
// For shininess, values between 10 (very large highlight) 
// and 200 (very small highlight) seem to work best, 
// though there is no actual upper bound.

typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
	t_pattern	pattern;
}	t_material;

typedef struct s_object
{
	t_point			loc;
	t_point			coi;
	t_vector		up;
	t_vector		rot;
	double			size;
	double			brightness;
	int				type;
	int				negative;
	size_t			id;
	t_matrix		transform;
	t_tuple			color;
	t_tuple			scale;
	t_material		material;
}					t_object;

typedef struct s_abc
{
	double			a;
	double			b;
	double			c;
}					t_abc;

typedef struct s_abcd
{
	double			a;
	double			b;
	double			c;
	double			d;
}					t_abcd;

typedef struct s_intersections
{
	t_vec			vec;
}					t_intersections;

typedef struct s_hit_record
{
	t_point			hit_loc;
	t_tuple			normal;
	double			hit_dist;
	int				clo_obj_id;
	union u_tuple	color;
	t_vector		to_eye;
	t_object		*object;
	int				inside;
}					t_hit_record;

typedef struct s_ray
{
	t_tuple			orig;
	t_tuple			dir;
	t_hit_record	hit;
	t_intersections	xs;
}					t_ray;

typedef struct s_intersection
{
	double			t;
	size_t			i;
	t_object		*object;
}					t_intersection;

typedef struct s_light
{
	t_point			location;
	t_vector		direction;
	t_color			intensity;
	int				type;
	t_point			pos;
}					t_light;
typedef struct s_negative
{
	double			t[2];
}				t_negative;




t_object			object_new(int shape_type);
double				calc_discriminant(double a, double b, double c);
t_ray				ray_new(t_point origin, t_vector dir);
t_ray				ray_new_malloc(t_point origin, t_vector dir);
t_ray				ray_new_no_malloc(t_point origin, t_vector dir);
void				ray_free(t_ray *ray);
t_point				ray_position(t_ray ray, double t);
int					phere_intersect(t_ray *ray, t_object *s);
t_ray				ray_transform(t_ray *source, t_matrix *transform);
void				intersection_record(
						t_ray *ray,
						double time,
						t_object *s);
void				intersection_record_test(
						t_ray *ray,
						double t1,
						double t2,
						t_object *s);
int					intersect_sphere(t_ray *inc_ray, t_object *s);
int					intersect_plane(t_ray *inc_ray, t_object *s);
int					intersect_cylinder(t_ray *inc_ray, t_object *s);
int					intersect_cone(t_ray *inc_ray, t_object *s);
t_intersection		intersection_new(double time, t_object *o);
t_intersection	find_closest_intersection(t_intersections *xs);
void				set_transform(t_object *obj, t_matrix *transform);
t_vector			normal_at(t_object *obj, t_point point);
t_material			material_new();
t_hit_record		precompute(t_intersection *intersection, t_ray *ray);

t_intersection	find_negative_object_intersect(t_ray *ray, int neg_obj_id, t_object *obj);


#endif
