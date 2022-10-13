/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:46:06 by mmakinen          #+#    #+#             */
/*   Updated: 2022/09/16 13:46:14 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_clamp(double num, double min, double max)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}
