/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 16:40:35 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

t_point	point_new(double x, double y, double z)
{
	t_point	r;

	r.s_xyzw.x = x;
	r.s_xyzw.y = y;
	r.s_xyzw.z = z;
	r.s_xyzw.w = 1.0;
	return (r);
}
