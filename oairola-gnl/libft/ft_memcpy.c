/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:50:29 by oairola           #+#    #+#             */
/*   Updated: 2021/11/23 09:05:17 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_copy;
	unsigned char	*src_copy;
	size_t			i;

	if (src == NULL && dst == NULL)
		return (NULL);
	i = 0;
	src_copy = (unsigned char *)src;
	dst_copy = (unsigned char *)dst;
	while (i < n)
	{
		dst_copy[i] = src_copy[i];
		i++;
	}
	return (dst_copy);
}
