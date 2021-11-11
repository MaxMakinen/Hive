/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:30:37 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/11 14:41:22 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*srcp;
	unsigned char	*dstp;
	int				count;

	count = 0;
	*srcp = src;
	*dstp = dst;
	if (srcp < dstp && dstp < srcp + len)
	{
		srcp += len;
		dstp += len;
		while (len-- != 0)
		{
			*--dstp = *--srcp;
		}
	}
	else
	{
		while (len-- != 0)
		{
			*dstp++ = *srcp++;
		}
	}
	return (dst);
}
