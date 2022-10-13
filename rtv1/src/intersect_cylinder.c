/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:02:15 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 09:02:18 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	cylinder_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1)
{
	double		q_f[3];
	double		dir;
	double		orig;
	t_vec3f		origin;

	origin = vec_minus(ray->orig, obj->pos);
	dir = dot_product(ray->dir, obj->dir);
	orig = dot_product(origin, obj->dir);
	q_f[0] = dot_product(ray->dir, ray->dir) - (dir * dir);
	q_f[1] = 2.0f * ((dot_product(ray->dir, origin) - (dir * orig)));
	q_f[2] = dot_product(origin, origin) - (orig * orig) - obj->radius2;
	if (!quadratic_formula(q_f, t0, t1))
		return (FALSE);
	if (*t0 > *t1 || *t0 < 0)
	{
		ft_swapf(t0, t1);
		if (*t0 < 0.0f)
		{
			*t0 = *t1;
			if (*t0 < 0.0f)
				return (FALSE);
		}
	}
	return (TRUE);
}
