/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:40:35 by jjuntune          #+#    #+#             */
/*   Updated: 2021/11/29 13:13:00 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	size_t	i;
	unsigned char *uc;
	unsigned char *dest;

	uc = (unsigned char *)s;
	dest = (unsigned char *)d;
	i = 0;
	while (i < n)
	{
		dest[i] = uc[i];
		if (uc[i] == (unsigned char)c)
			return ((void *)dest);
		i++;
	}
	return (NULL);
}
