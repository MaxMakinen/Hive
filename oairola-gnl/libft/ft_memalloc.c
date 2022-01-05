/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:49:01 by oairola           #+#    #+#             */
/*   Updated: 2021/12/13 10:01:32 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*i;
	size_t			a;

	a = 0;
	i = (unsigned char *)malloc(size);
	if (i == NULL)
		return (NULL);
	while (a != size)
	{
		i[a] = 0;
		a++;
	}
	i = (void *)i;
	return (i);
}
