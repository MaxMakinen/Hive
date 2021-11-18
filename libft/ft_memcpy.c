/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:21:42 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/18 14:28:01 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dstp;
	const char	*srcp;
	size_t		count;

	count = 0;
	if (n == 0 || dst == src)
		return (dst);
	while (count < n)
	{
		dst[count] = src[count];
		count++;
	}
	return (dst);
}
