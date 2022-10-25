/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:28:17 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/13 10:35:22 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	quadratic_formula(double *input, double *t0, double *t1)
{
	double	discriminant;
	double	temp;

	discriminant = input[1] * input[1] - 4.0f * input[0] * input[2];
	if (discriminant > 0.0f)
	{
		if (input[1] > 0)
			temp = -0.5 * (input[1] + sqrtf(discriminant));
		else
			temp = -0.5 * (input[1] - sqrtf(discriminant));
		*t1 = temp / input[0];
		*t0 = input[2] / temp;
		return (TRUE);
	}
	else if (discriminant == 0)
	{
		*t0 = -0.5f * input[1] / input[0];
		*t1 = *t0;
		return (TRUE);
	}
	return (FALSE);
}
