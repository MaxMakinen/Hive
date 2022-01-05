/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:11:39 by oairola           #+#    #+#             */
/*   Updated: 2021/12/13 10:02:03 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	unsigned char	*array;
	size_t			a;

	a = 0;
	array = (unsigned char *)malloc(size + 1);
	if (array == NULL)
		return (NULL);
	while (a != size)
	{
		array[a] = '\0';
		a++;
	}
	array[a] = '\0';
	return ((char *)array);
}
