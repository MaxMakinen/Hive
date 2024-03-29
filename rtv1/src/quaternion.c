/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:18:35 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 13:18:42 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	quat_init(t_quat *quat)
{
	*quat = (t_quat){0.0, 0.0, 0.0, 1.0};
}

/*creates quaternion from axis angle pair*/
void	quat_from_axis_angle(t_vec3f *axis, double angle, t_quat *quat)
{
	double	temp;

	temp = sin(angle * 0.5);
	quat->w = cos(angle * 0.5);
	quat->x = axis->x * temp;
	quat->y = axis->y * temp;
	quat->z = axis->z * temp;
}

/*utility function for quat_rotate*/
void	quat_rot_prep(t_quat *quat, double *temp)
{
	temp[0] = quat->w * quat->w;
	temp[1] = quat->x * quat->x;
	temp[2] = quat->y * quat->y;
	temp[3] = quat->z * quat->z;
	temp[4] = quat->w * quat->x;
	temp[5] = quat->w * quat->y;
	temp[6] = quat->w * quat->z;
	temp[7] = quat->x * quat->y;
	temp[8] = quat->x * quat->z;
	temp[9] = quat->y * quat->z;
}

/*Rotates vector with quaternion, outputs rotated vector*/
void	quat_rotate(t_quat *quat, t_vec3f *point, t_vec3f *output)
{
	double	temp[10];

	quat_rot_prep(quat, temp);
	output->x = temp[0] * point->x + 2 * temp[5] * point->z - 2 * temp[6] * \
	point->y + temp[1] * point->x + 2 * temp[7] * point->y + 2 * temp[8] * \
	point->z - temp[3] * point->x - temp[2] * point->x;
	output->y = 2 * temp[7] * point->x + temp[2] * point->y + 2 * temp[9] * \
	point->z + 2 * temp[6] * point->x - temp[3] * point->y + temp[0] * \
	point->y - 2 * temp[4] * point->z - temp[1] * point->y;
	output->z = 2 * temp[8] * point->x + 2 * temp[9] * point->y + temp[3] * \
	point->z - 2 * temp[5] * point->x - temp[2] * point->z + 2 * temp[4] * \
	point->y - temp[1] * point->z + temp[0] * point->z;
}

/*multiplies two quaternions together and outputs the result*/
void	quat_multiply(t_quat *q1, t_quat *q2, t_quat *output)
{
	output->w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
	output->x = q1->x * q2->w + q1->w * q2->x + q1->y * q2->z - q1->z * q2->y;
	output->y = q1->w * q2->y - q1->x * q2->z + q1->y * q2->w + q1->z * q2->x;
	output->z = q1->w * q2->z + q1->x * q2->y - q1->y * q2->x + q1->z * q2->w;
}
