/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:19:43 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 13:20:03 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	rad_to_deg(double rad)
{
	return (rad * M_PI / 180);
}

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180));
}

double	quat_len(t_quat *quat)
{
	return (sqrt(quat->x * quat->x + quat->y * quat->y + quat->z * quat->z + \
	quat->w * quat->w));
}

t_quat	quat_normalize(t_quat *quat)
{
	double	len;

	len = quat_len(quat);
	len = 1 / len;
	return ((t_quat){quat->x * len, quat->y * len, quat->z * len, \
	quat->w * len});
}

t_quat	quat_conjugate(t_quat *quat)
{
	return ((t_quat){-quat->x, -quat->y, -quat->z, quat->w});
}
