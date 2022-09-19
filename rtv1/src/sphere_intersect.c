
#include "rtv1.h"

int	sphere_intersect(t_scene *scene, t_vec3f origin, t_vec3f direction, float radius2, float *t0, float *t1)
{
	float		a;
	float		b;
	float		c;

	a = dot_product(direction, direction);
	b = 2.0f * dot_product(origin, direction);
	c = dot_product(origin, origin) - radius2;
	
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