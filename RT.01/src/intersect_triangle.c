#include "rtv1.h"

int	triangle_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1)
{
	t_vec3f edge1, edge2;
	t_vec3f h, s, q;
	double	a, f, u, v, t;
	
	edge1 = vec_minus(obj->vertex1, obj->vertex0);
	edge2 = vec_minus(obj->vertex2, obj->vertex0);
	h = cross_product(ray->dir, edge2);
	a = dot_product(edge1, h);
	if (a > -EPSILON && a < EPSILON)
		return (FALSE);
	f = 1.0 / a;
	s = vec_minus(ray->orig, obj->vertex0);
	u = f * dot_product(s, h);
	if (u < 0.0 || u > 1.0)
		return (FALSE);
	q = cross_product(s, edge1);
	v = f * dot_product(ray->dir, q);
	if (v < 0.0 || v + u > 1.0)
		return (FALSE);
	t = f * dot_product(edge2, q);
	if (t > EPSILON)
	{
		*t0 = t;
		return (TRUE);
	}
	else
		return (FALSE);
	}