/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_coi_transform.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:28:28 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/28 17:52:57 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_matrix	coi_transform(t_cam *cam, t_matrix transform)
{
	t_tuple		transform_coi;	
	t_matrix	result;
	t_matrix	rotation;
	double		rot_x;
	double		rot_y;
	double		rot_z;

	result = matrix_inverse(&transform);
	transform_coi = matrix_tuple_multiply(&result, &cam->coi);
	
	transform_coi = vector_new(transform_coi.s_xyzw.x,
								transform_coi.s_xyzw.y,
								transform_coi.s_xyzw.z);
	result = transform;
	rot_x = atan2(transform_coi.s_xyzw.y, transform_coi.s_xyzw.z);
	rot_y = atan2(transform_coi.s_xyzw.x, transform_coi.s_xyzw.z);
	rot_z = atan2(transform_coi.s_xyzw.y, transform_coi.s_xyzw.x);
	rotation = matrix_rotate_x(rot_x);
	result = matrix_multiply(&result, &rotation);
	rotation = matrix_rotate_y(rot_y);
	result = matrix_multiply(&result, &rotation);
	rotation = matrix_rotate_z(rot_z);
	result = matrix_multiply(&result, &rotation);
	return(result);
}
