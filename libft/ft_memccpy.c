/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:30:11 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/11 13:10:44 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	uc;
	unsigned char	*srcp;
	unsigned char	*dstp;
	size_t			count;

	srcp = src;
	dstp = dst;
	uc = c;
	count = 0;
	while (count <= n)
	{
		dstp[count] = srcp[count];
		if (dstp[count] == uc)
			return (dstp[count + 1]);
		count++;
	}
	return (NULL);
}
