/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cross.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 17:41:38 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

t_vector	vector_cross(t_vector u, t_vector v)
{
	t_vector	crossed;

	crossed.s_xyzw.x = u.s_xyzw.y * v.s_xyzw.z - u.s_xyzw.z * v.s_xyzw.y;
	crossed.s_xyzw.y = u.s_xyzw.z * v.s_xyzw.x - u.s_xyzw.x * v.s_xyzw.z;
	crossed.s_xyzw.z = u.s_xyzw.x * v.s_xyzw.y - u.s_xyzw.y * v.s_xyzw.x;
	crossed.s_xyzw.w = 0.0;
	return (crossed);
}
