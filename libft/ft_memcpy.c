/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:21:42 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/25 14:56:47 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dstp;
	const char	*srcp;
	const char	*end;

	if (n == 0 || dst == src)
		return (dst);
	dstp = (char *)dst;
	srcp = (const char *)src;
	end = srcp + n;
	while (srcp < end)
	{
		*dstp++ = *srcp++;
	}
	return (dst);
}
