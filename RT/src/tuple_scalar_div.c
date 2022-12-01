/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_scalar_div.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/09 15:02:47 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

t_tuple	tuple_scalar_div(t_tuple u, double x)
{
	t_tuple	r;


	if (u.s_xyzw.x == 0.0 && x == 0.0)
		r.s_xyzw.x = 0;
	else
		r.s_xyzw.x = u.s_xyzw.x / x;
	if (u.s_xyzw.y == 0.0 && x == 0.0)
		r.s_xyzw.y = 0;
	else
		r.s_xyzw.y = u.s_xyzw.y / x;
	if (u.s_xyzw.z == 0.0 && x == 0.0)
		r.s_xyzw.z = 0;
	else
		r.s_xyzw.z = u.s_xyzw.z / x;
	if (u.s_xyzw.w == 0.0 && x == 0.0)
		r.s_xyzw.w = 0;
	else
		r.s_xyzw.w = u.s_xyzw.w / x;
	return (r);
}
