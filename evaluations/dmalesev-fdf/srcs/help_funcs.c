/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:47:31 by dmalesev          #+#    #+#             */
/*   Updated: 2022/05/03 14:48:00 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	int_to_bit(int nbr)
{
	return (1 << (nbr - 1));
}

void	rot_overflows(t_utils *utils)
{
	if (utils->rot.alpha > 360)
		utils->rot.alpha = 0;
	else if (utils->rot.alpha < 0)
		utils->rot.alpha = 360;
	if (utils->rot.beta > 360)
		utils->rot.beta = 0;
	else if (utils->rot.beta < 0)
		utils->rot.beta = 360;
}
