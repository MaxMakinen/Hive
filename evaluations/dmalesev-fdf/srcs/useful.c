/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:26:24 by dmalesev          #+#    #+#             */
/*   Updated: 2022/04/27 13:13:53 by dmalesev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_map(t_utils *utils)
{
	int	i;
	int	j;

	i = 0;
	while (i < utils->lines)
	{
		j = 0;
		while (j <= utils->map[i][0])
		{
			ft_putnbr(utils->map[i][j]);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
