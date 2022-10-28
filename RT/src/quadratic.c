/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:20:53 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/17 18:21:46 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

double	calc_b2_4ac(t_abc abc)
{
	return ((abc.b * abc.b) - (4 * abc.a * abc.c));
}

double	quadratic(t_abc abc, double b2_4ac)
{
	double	result_m;
	double	result_p;

	result_m = ((-abc.b - sqrt(b2_4ac)) / (2 * abc.a));
	result_p = ((-abc.b + sqrt(b2_4ac)) / (2 * abc.a));
	if (result_p < result_m && result_p > 0.0)
		return (result_p);
	else
		return (result_m);
	return (-1);
}
