/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:59:16 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/15 16:23:50 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	unsigned char	*p1;
	unsigned char	*p2;
	unsigned char	*end1;

	p1 = *dst;
	p2 = *src;
	end1 = p1 + len;
	while (p2 != '\0' && p1 != end1)
		p1++ = p2++;
	if (p1 < end1)
		p1++ = 0;
	p1 = '\0';
	return (dst);
}
