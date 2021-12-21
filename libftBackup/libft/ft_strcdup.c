/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:06:10 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/09 11:44:44 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *s1, const int c)
{
	char	*str;
	size_t	size;

	if (s1 != 0)
	{
		size = ft_strlenc(s1, c);
		if (size != 0)
		{
			str = ft_strnew(size);
			if (str == NULL)
				return (NULL);
			ft_memcpy(str, s1, size);
			return (str);
		}
		return (0);
	}
	return (NULL);
}
