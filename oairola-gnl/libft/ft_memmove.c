/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:36:43 by oairola           #+#    #+#             */
/*   Updated: 2021/11/30 09:37:26 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_copy;
	unsigned char	*src_copy;
	size_t			i;

	i = -1;
	if (src == NULL && dst == NULL)
		return (NULL);
	src_copy = (unsigned char *)src;
	dst_copy = (unsigned char *)dst;
	if (src_copy > dst_copy)
	{
		while (++i < len)
		{
			dst_copy[i] = src_copy[i];
		}
	}
	else
	{	
		while (0 < len)
		{
			dst_copy[len - 1] = src_copy[len - 1];
			len--;
		}
	}
	return (dst_copy);
}
