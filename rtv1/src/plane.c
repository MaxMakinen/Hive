
#include "rtv1.h"


int	plane_intersect(t_scene *scene, t_ray *ray, t_obj *obj, double *t0, double *t1)
{
	double	denominator;
	t_vec3f	normal;
	t_vec3f		origin;

//	origin = vec_minus(ray->orig, obj->pos);
	origin = vec_minus(obj->pos, ray->orig);


	normal = normalize(obj->dir);

	ray->dir = normalize(ray->dir);
	*t1 = 0.0f;
	denominator = dot_product(normal, ray->dir);
	if (fabs(denominator) > 0.000001f)
	{
		*t0 = dot_product(origin, normal) / denominator;
		if (*t0 >= 0)
			return (TRUE);
	}
	return (FALSE);
}
