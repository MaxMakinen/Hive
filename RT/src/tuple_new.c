/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 16:03:30 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

t_tuple	tuple_new(double x, double y, double z, double w)
{
	t_tuple	r;

	r.s_xyzw.x = x;
	r.s_xyzw.y = y;
	r.s_xyzw.z = z;
	r.s_xyzw.w = w;
	return (r);
}
