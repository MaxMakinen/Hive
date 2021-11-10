/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:17:06 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/10 13:29:04 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*memory;
	int		count;

	memory = (void *)malloc(sizeof(memory) * size);
	if (memory == 0)
		return (NULL);
	while (count <= size)
	{
		memory[count] = 0;
		count++;
	}
	return (memory);
}
