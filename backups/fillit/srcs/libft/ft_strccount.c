/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:22:40 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/19 19:42:25 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
function to count amount of c characters in str
*/

int	ft_strccount(char *str, int c)
{
	int				count;
	int				index;
	unsigned char	uc;

	uc = (unsigned char)c;
	count = 0;
	index = 0;
	if (!str)
		return (-1);
	while (str[index])
	{
		if (str[index] == uc)
			count++;
		index++;
	}
	if (c == 0)
		count++;
	return (count);
}
