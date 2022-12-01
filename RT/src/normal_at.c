/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:08:01 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/15 17:39:00 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include "object.h"
#include <math.h>


t_vector	normal_at(t_object *obj, t_point point)
{
	t_point		obj_point;
	t_vector	obj_normal;
	t_vector	world_normal;
	t_matrix	inverse;

	inverse = matrix_inverse(&obj->transform);
	obj_point =	matrix_tuple_multiply(&inverse, &point);
	if (obj->type == SPHERE)
		obj_normal = tuple_sub(obj_point,  point_new(0, 0, 0));
 	if (obj->type == CYLINDER)
	{
		obj_normal = obj_point;
		obj_normal.s_xyzw.y = 0; 
	}
	if (obj->type == PLANE)
		obj_normal = vector_new(0, 1, 0);
	if (obj->type == CONE)
	{
		obj_normal = obj_point;
		obj_normal.s_xyzw.y = sqrt(obj_point.s_xyzw.x * obj_point.s_xyzw.x + 
									obj_point.s_xyzw.z * obj_point.s_xyzw.z);
		if (obj_point.s_xyzw.y > 0)
			obj_normal.s_xyzw.y = -obj_normal.s_xyzw.y;
		/* obj_normal = tuple_neg(obj_normal); */
	}
	
	matrix_transpose(&inverse);
	world_normal = matrix_tuple_multiply(&inverse, &obj_normal);
	world_normal.s_xyzw.w = 0;
	return (tuple_unit(world_normal));
}