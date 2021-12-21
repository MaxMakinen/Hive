/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:32:25 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/15 12:47:18 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (s)
	{
		while (*s != '\0')
		{
			if (*s == uc)
				return ((char *)s);
			s++;
		}
		if (c == 0)
			return ((char *)s);
	}
	return (NULL);
}
