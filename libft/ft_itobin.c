/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itobin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:05:29 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/08 18:28:23 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
function to turn unsigned int to binary for printing.
*/

char	*ft_itobin(unsigned int num)
{
	int				len;
	char			*answer;

	len = (sizeof(num) * 8);
	answer = ft_strnew(len--);
	while (len > 0)
	{
		if ((num >> len) & 1)
			break ;
		len--;
	}
	while (len >= 0)
	{
		if ((num >> len) & 1)
			ft_strcat(answer, "1");
		else
			ft_strcat(answer, "0");
		len--;
	}
	return (answer);
}
