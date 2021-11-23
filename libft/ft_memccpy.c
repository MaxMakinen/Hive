/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:30:11 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/23 13:40:09 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*srcp;
	unsigned char	*dstp;
	unsigned char	*end;

	srcp = (unsigned char *)src;
	dstp = (unsigned char *)dst;
	end = srcp + n;
	while (srcp < end && *srcp != (unsigned char)c)
	{
		*dstp++ = *srcp++;
	}
	if (srcp >= end && *srcp != (unsigned char)c)
		return (NULL);
	if (srcp != end && *srcp == (unsigned char)c)
		*dstp++ = *srcp;
	return (dstp);
}
