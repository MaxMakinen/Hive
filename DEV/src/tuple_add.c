/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 16:30:54 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

t_tuple	tuple_add(t_tuple u, t_tuple v)
{
	t_tuple	r;

	r.s_xyzw.x = u.s_xyzw.x + v.s_xyzw.x;
	r.s_xyzw.y = u.s_xyzw.y + v.s_xyzw.y;
	r.s_xyzw.z = u.s_xyzw.z + v.s_xyzw.z;
	r.s_xyzw.w = u.s_xyzw.w + v.s_xyzw.w;
	return (r);
}
