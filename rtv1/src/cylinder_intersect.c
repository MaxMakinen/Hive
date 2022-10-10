#include "rtv1.h"

int	cylinder_intersect(t_scene *scene, t_ray *ray, t_obj *obj, double *t0, double *t1)
{
	double		a;
	double		b;
	double		c;
	double		dir;
	double		orig;
	t_vec3f		normal;
	t_vec3f		origin;

	origin = vec_minus(ray->orig, obj->pos);

	normal = normalize(obj->dir);
	dir = dot_product(ray->dir, normal);
	orig = dot_product(origin, normal);
	a = dot_product(ray->dir, ray->dir) - (dir * dir);
	b = 2.0f * ((dot_product(ray->dir, origin) - (dot_product(ray->dir, normal) * orig)));
	c = dot_product(origin, origin) - (orig * orig) - obj->radius2;
	
	if (!quadratic_formula(a, b, c, t0, t1))
		return (FALSE);
	if (*t0 > *t1 || *t0 < 0)
	{
		ft_swapf(t0, t1);
		if (*t0 < 0.0f)
		{
			*t0 = *t1;
			if (*t0 < 0.0f)
				return(FALSE);
		}
	}
	return (TRUE);
}