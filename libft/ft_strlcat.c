/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:43:03 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/24 10:31:37 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*printer;
	const char	*reader;
	size_t		siz;
	size_t		dstlen;
	size_t		srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	printer = dst + dstlen;
	reader = src;
	siz = dstsize - dstlen;
	if ((dstlen + 1) > dstsize)
		return (dstsize + srclen);
	if ((dstlen + 1) < dstsize)
	{
		while (siz > 1)
		{
			*printer++ = *reader++;
			siz--;
		}
	*printer = '\0';
	}
	return (dstlen + srclen);
}
