/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_dot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/09 16:07:04 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

double	vector_dot(t_tuple u, t_tuple v)
{
	double	r;

	r = u.s_xyzw.x * v.s_xyzw.x;
	r += u.s_xyzw.y * v.s_xyzw.y;
	r += u.s_xyzw.z * v.s_xyzw.z;
	r += u.s_xyzw.w * v.s_xyzw.w;
	return (r);
}
