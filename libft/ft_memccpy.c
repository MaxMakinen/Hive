/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:30:11 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/19 13:59:18 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	ch;
	const char	*srcp;
	unsigned char	*dstp;
	const char	*end;

	srcp = (const char *)src;
	dstp = (unsigned char *)dst;
	ch = (unsigned char)c;
	end = srcp + n;
	while (srcp < end || ch != c)
	{
		*dstp++ = ch = *srcp++;
	}
	if (srcp >= end && ch != c)
		return (NULL);
	return (dstp);
}
