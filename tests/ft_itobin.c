/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itobin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:05:29 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/19 13:07:50 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
function to turn unsigned int to binary for printing.
*/

unsigned long long	ft_itobin(unsigned int num)
{
	if (num == 0)
		return (0);
	if (num == 1)
		return (1);
	return ((num % 2) + 10 * binary(num / 2));
}
