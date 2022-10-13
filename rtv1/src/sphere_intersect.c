/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 08:58:26 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 08:58:51 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	sphere_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1)
{
	double		a;
	double		b;
	double		c;
	t_vec3f		origin;

	origin = vec_minus(ray->orig, obj->pos);
	a = dot_product(ray->dir, ray->dir);
	b = 2.0f * dot_product(ray->dir, origin);
	c = dot_product(origin, origin) - obj->radius2;
	if (!quadratic_formula(a, b, c, t0, t1))
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
