#include "rtv1.h"

/*AABB - Axis Aligned Bounding Box. Using the Slab method*/
int	aabb_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1)
{
	double	tmin;
	double	tmax;
	double	temp[2];

	tmin = -INFINITY;
	tmax = INFINITY;
	/*Move this to ray creation, make part of ray sturct*/
	//invdir = (t_vec3f){1 / ray->dir.x, 1 / ray->dir.y, 1 / ray->dir.z};

	temp[0] = (obj->bb_min.x - ray->orig.x) * ray->inv_dir.x;
	temp[1] = (obj->bb_max.x - ray->orig.x) * ray->inv_dir.x;
	
	tmin = ft_min(temp[0], temp[1]);
	tmax = ft_max(temp[0], temp[1]);

	temp[0] = (obj->bb_min.y - ray->orig.y) * ray->inv_dir.y;
	temp[1] = (obj->bb_max.y - ray->orig.y) * ray->inv_dir.y;
	
	tmin = ft_max(tmin, ft_min(temp[0], temp[1]));
	tmax = ft_min(tmax, ft_max(temp[0], temp[1]));

	temp[0] = (obj->bb_min.z - ray->orig.z) * ray->inv_dir.z;
	temp[1] = (obj->bb_max.z - ray->orig.z) * ray->inv_dir.z;
	
	tmin = ft_max(tmin, ft_min(temp[0], temp[1]));
	tmax = ft_min(tmax, ft_max(temp[0], temp[1]));

	*t1 = tmax;
	*t0 = tmin;
	return (tmax >= ft_max(0.0, tmin));
}