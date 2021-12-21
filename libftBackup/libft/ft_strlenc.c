/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:04:31 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/09 16:52:59 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlenc(const char *s, int c)
{
	size_t			count;
	unsigned char	uc;

	uc = (unsigned char)c;
	count = 0;
	if (s)
	{
		while (s[count] != '\0')
		{
			if (s[count] == uc)
				return (count);
			count++;
		}
	}
	return (0);
}
