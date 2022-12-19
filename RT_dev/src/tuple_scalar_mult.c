/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_scalar_mult.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 16:49:59 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

t_tuple	tuple_scalar_mult(t_tuple u, double x)
{
	t_tuple	r;

	r.s_xyzw.x = u.s_xyzw.x * x;
	r.s_xyzw.y = u.s_xyzw.y * x;
	r.s_xyzw.z = u.s_xyzw.z * x;
	r.s_xyzw.w = u.s_xyzw.w * x;
	return (r);
}
