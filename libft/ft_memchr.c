/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:41:54 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/11 15:30:10 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*str;
	int				count;

	*str = s;
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
	return(NULL);
}

