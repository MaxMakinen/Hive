/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:24:33 by oairola           #+#    #+#             */
/*   Updated: 2021/11/30 14:36:14 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{	
	size_t	i;
	size_t	a;
	size_t	len_dst;
	size_t	len_src;

	a = 0;
	i = 0;
	len_src = ft_strlen(src);
	while (dst[i] != '\0')
		i++;
	if (i > dstsize)
		len_dst = dstsize;
	else
		len_dst = i;
	if (dstsize != 0)
	{
		while (src[a] && i < dstsize - 1)
			dst[i++] = src[a++];
	}
	dst[i] = '\0';
	return (len_dst + len_src);
}
