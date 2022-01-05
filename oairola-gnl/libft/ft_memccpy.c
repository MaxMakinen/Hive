/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:52:56 by oairola           #+#    #+#             */
/*   Updated: 2021/11/29 14:11:18 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_copy;
	unsigned char	*src_copy;
	size_t			i;

	i = 0;
	c = (unsigned char)c;
	src_copy = (unsigned char *)src;
	dst_copy = (unsigned char *)dst;
	while (i < n)
	{
		dst_copy[i] = src_copy[i];
		if (dst_copy[i] == (unsigned char)c)
		{
			dst = dst + '\0';
			return (&dst[i + 1]);
		}
		i++;
	}
	return (0);
}
