/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:28:17 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 13:28:19 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	quadratic_formula(double a, double b, double c, double *t0, double *t1)
{
	double	discriminant;
	double	temp;

	discriminant = b * b - 4.0f * a * c;
	if (discriminant > 0.0f)
	{
		if (b > 0)
			temp = -0.5 * (b + sqrtf(discriminant));
		else
			temp = -0.5 * (b - sqrtf(discriminant));
		*t1 = temp / a;
		*t0 = c / temp;
		return (TRUE);
	}
	else if (discriminant == 0)
	{
		*t0 = -0.5f * b / a;
		*t1 = *t0;
		return (TRUE);
	}
	return (FALSE);
}