/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_coi_transform.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:28:28 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/07 11:30:03 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

double	double_p2(double src)
{
	return (src * src);
}

double	double_div(double a, double b)
{
	if (a == 0 || b == 0)
		return (0.0);
	return (a / b);
}

double	calc_y_rot(t_tuple a, t_tuple b)
{
	return (acos(
			double_div(
				(a.s_xyzw.x * b.s_xyzw.x + a.s_xyzw.z * b.s_xyzw.z),
				(sqrt((double_p2(a.s_xyzw.x) + double_p2(a.s_xyzw.z))))
				* sqrt((double_p2(b.s_xyzw.x) + double_p2(b.s_xyzw.z))))));
}

double	calc_x_rot(t_tuple a, t_tuple b)
{
	return (acos(
			double_div(
				(a.s_xyzw.x * b.s_xyzw.x + a.s_xyzw.y
					* b.s_xyzw.y + a.s_xyzw.z * b.s_xyzw.z),
				(sqrt((double_p2(a.s_xyzw.x)
							+ double_p2(a.s_xyzw.y)
							+ double_p2(a.s_xyzw.z))))
				* sqrt((double_p2(b.s_xyzw.x)
						+ double_p2(b.s_xyzw.y)
						+ double_p2(b.s_xyzw.z))))));
}

t_matrix	coi_transform(t_cam *cam, t_matrix transform)
{
	t_tuple		b;
	t_matrix	result;
	t_matrix	rotation;
	t_ray		temp;
	double		rot;

	result = matrix_inverse(&transform);
	b = matrix_tuple_multiply(&cam->coi_transform, &cam->coi);
	b = matrix_tuple_multiply(&result, &b);
	b.s_xyzw.w = 0;
	temp = ray_new_no_malloc(cam->pos, cam->n);
	result = transform;
	rot = calc_y_rot(temp.dir, b);
	if (temp.dir.s_xyzw.x > b.s_xyzw.x)
		rot = -rot;
	rotation = matrix_rotate_y(rot);
	temp = ray_transform(&temp, &rotation);
	result = matrix_multiply(&result, &rotation);
	rot = calc_x_rot(temp.dir, b);
	if (temp.dir.s_xyzw.y < b.s_xyzw.y)
		rot = -rot;
	rotation = matrix_rotate_x(rot);
	result = matrix_multiply(&result, &rotation);
	temp = ray_transform(&temp, &rotation);
	return (result);
}
