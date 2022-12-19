/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noice_maths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:07:52 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/12 14:08:50 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15;
	if (h < 8)
		u = x;
	else
		u = y;
	if (h < 4)
		v = y;
	else if (h == 12 || h == 14)
		v = z;
	else
		v = x;
	if ((h & 1) == 0)
	{
		if ((h & 2) == 0)
			return (u + v);
		return (u + -v);
	}
	if ((h & 2) == 0)
		return (-u + v);
	return (-u + -v);
}
