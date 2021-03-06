/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itobin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:05:29 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/08 12:35:24 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
function to turn unsigned int to binary for printing.
*/

char	*ft_itobin(unsigned int num)
{
	unsigned int	len;
	unsigned int	count;
	char			*answer;

	len = (sizeof(num) * 8);
	count = 0;
	answer = ft_strnew(len);

	while (count < len)
	{
		if ((num >> count) & 1)
			answer = ft_strcat(answer, "1");
		else
			answer = ft_strcat(answer, "0");
		count++;
	}	
	return (answer);
}

int main(void)
{
	unsigned int	x;
	char			*bin;

	x = 12;
	bin = ft_itobin(x);
	printf("%s",bin);
	return (0);
}
