
#include "rtv1.h"

int	cone_intersect(t_scene *scene, t_ray *ray, t_obj *obj, double *t0, double *t1)
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
	double	height = obj->height;
	double	M_Con = obj->radius2 / (height * height);
	double	dir2 = dir * dir;
	double	orig2 = orig * orig;
	double	dir_orig = dir * orig;

	a = dot_product(ray->dir, ray->dir) - (M_Con * dir2) - dir2;
	b = 2.0f * (dot_product(ray->dir, origin) - (M_Con * dir_orig) - dir_orig);
	c = dot_product(origin, origin) - M_Con * orig2 - orig2;
	
	if (!quadratic_formula(a, b, c, t0, t1))
		return (FALSE);
	if (*t0 > *t1)
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