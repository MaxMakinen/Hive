#include "rtv1.h"

/*AABB - Axis Aligned Bounding Box. Using the Slab method*/
int	aabb_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1)
{
	t_vec3f	invdir;
	double	tmin;
	double	tmax;
	double	temp[2];

	tmin = -INFINITY;
	tmax = INFINITY;
	invdir = (t_vec3f){1 / ray->dir.x, 1 / ray->dir.y, 1 / ray->dir.z};

	temp[0] = (obj->bb_min.x - ray->orig.x) * invdir.x;
	temp[1] = (obj->bb_max.x - ray->orig.x) * invdir.x;
	
	tmin = ft_min(temp[0], temp[1]);
	tmax = ft_max(temp[0], temp[1]);

	temp[0] = (obj->bb_min.y - ray->orig.y) * invdir.y;
	temp[1] = (obj->bb_max.y - ray->orig.y) * invdir.y;
	
	tmin = ft_max(tmin, ft_min(temp[0], temp[1]));
	tmax = ft_min(tmax, ft_max(temp[0], temp[1]));

	temp[0] = (obj->bb_min.z - ray->orig.z) * invdir.z;
	temp[1] = (obj->bb_max.z - ray->orig.z) * invdir.z;
	
	tmin = ft_max(tmin, ft_min(temp[0], temp[1]));
	tmax = ft_min(tmax, ft_max(temp[0], temp[1]));

	*t1 = tmax;
	*t0 = tmin;
	return (tmax >= ft_max(0.0, tmin));
}