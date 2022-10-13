/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:12:19 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 09:12:27 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	pre_calculate(t_ray *ray, t_obj *obj, double *pre_c, t_vec3f *orig)
{
	pre_c[0] = dot_product(ray->dir, obj->dir);
	pre_c[1] = dot_product(*orig, obj->dir);
	pre_c[2] = obj->radius2 / (obj->height * obj->height);
	pre_c[3] = pre_c[0] * pre_c[0];
	pre_c[4] = pre_c[1] * pre_c[1];
	pre_c[5] = pre_c[0] * pre_c[1];
}

int	cone_intersect(t_ray *ray, t_obj *obj, double *t0, double *t1)
{
	double	q_f[3];
	double	pre_c[6];
	t_vec3f	origin;

	origin = vec_minus(ray->orig, obj->pos);
	pre_calculate(ray, obj, pre_c, &origin);
	q_f[0] = dot_product(ray->dir, ray->dir) - (pre_c[2] * pre_c[3]) - pre_c[3];
	q_f[1] = 2.0f * (dot_product(ray->dir, origin) - \
	(pre_c[2] * pre_c[5]) - pre_c[5]);
	q_f[2] = dot_product(origin, origin) - pre_c[2] * pre_c[4] - pre_c[4];
	if (!quadratic_formula(q_f[0], q_f[1], q_f[2], t0, t1))
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
