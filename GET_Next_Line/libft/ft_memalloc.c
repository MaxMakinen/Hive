/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:17:06 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/19 11:41:21 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*memory;

	memory = (void *)malloc(sizeof(memory) * size);
	if (memory == 0)
		return (NULL);
	ft_bzero(memory, size);
	return (memory);
}
