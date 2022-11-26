/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_mag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 16:48:21 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include <math.h>

double	tuple_mag(t_tuple u)
{
	double	r;

	r = u.s_xyzw.x * u.s_xyzw.x;
	r += u.s_xyzw.y * u.s_xyzw.y;
	r += u.s_xyzw.z * u.s_xyzw.z;
	r += u.s_xyzw.w * u.s_xyzw.w;
	return (sqrt(r));
}
