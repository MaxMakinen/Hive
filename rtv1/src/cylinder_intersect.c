#include "rtv1.h"

int	cylinder_intersect(t_scene *scene, t_vec3f origin, t_vec3f direction, t_obj *object, float *t0, float *t1)
{
	float		a;
	float		b;
	float		c;
	double		dir;
	double		orig;
	t_vec3f		normal;

	normal = normalize(object->dir);
	dir = dot_product(direction, normal);
	orig = dot_product(origin, normal);
	a = dot_product(direction, direction) - (dir * dir);
	b = 2.0f * ((dot_product(direction, origin) - (dot_product(direction, normal) * orig)));
	c = dot_product(origin, origin) - (orig * orig) - object->radius2;
	
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