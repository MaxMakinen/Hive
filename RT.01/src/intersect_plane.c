/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:32:17 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 09:32:23 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	plane_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1)
{
	double	denominator;
	t_vec3f	normal;
	t_vec3f	origin;

	origin = vec_minus(obj->pos, ray->orig);
	*t1 = 0.0f;
	denominator = dot_product(obj->dir, ray->dir);
	if (fabs(denominator) > 0.000001f)
	{
		*t0 = dot_product(origin, obj->dir) / denominator;
		if (*t0 >= 0)
			return (TRUE);
	}
	return (FALSE);
}

int	disc_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1)
{
	t_vec3f intersect;

	if (plane_intersect(ray, obj, t0, t1))
	{
		if(vec_len(vec_minus(get_intersect(ray->orig, ray->dir, *t0), obj->pos)) <= obj->radius)
			return (TRUE);
	}
	*t0 = INFINITY;
	return (FALSE);
}