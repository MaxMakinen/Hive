/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:41:47 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 09:41:50 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	ft_floor(double num)
{
	float	neg;

	neg = 1;
	if (num == 0)
		return (0.0);
	if (num < 0)
	{
		neg = -1;
		num *= -1;
		if (num > 0)
			num += 1.0;
	}
	num = (int)num;
	return (num * neg);
}
