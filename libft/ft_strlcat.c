/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:43:03 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/23 21:30:16 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*printer;
	const char	*reader;
	size_t		siz;
	size_t		dstlen;

	printer = dst;
	reader = src;
	siz = dstsize;
	while (*printer != '\0' && siz-- != 0)
		printer++;
	dstlen = printer - dst;
	siz = dstsize - dstlen;
	if (siz == 0)
		return (dstlen + ft_strlen(src));
	while (*reader != '\0' && siz > 1)
	{
			*printer++ = *reader++;
			siz--;
	}
	*printer = '\0';
	return (dstlen + (reader - src) - 1);
}
