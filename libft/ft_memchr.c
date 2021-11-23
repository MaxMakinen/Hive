/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:41:54 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/19 11:59:30 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*str;
	size_t				count;

	str = (unsigned char *)s;
	ch = c;
	count = 0;
	while (count <= n)
	{
		if (str[count] == ch)
		{
			return (&str[count]);
		}
		count++;
	}
	return (NULL);
}
