/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:10:07 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/03 11:29:40 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	long	size;
	int		*range;
	int		count;

	count = 0;
	if (min >= max)
		return (0);
	size = min - max;
	if (size < 0)
		size *= -1;
	if (size > 2147483647)
		return (0);
	while ((min + size) > max)
		size++;
	range = malloc(sizeof(range) * size + 1);
	if (range == 0)
		return (0);
	while ((min + count) < max)
	{
		range[count] = min + count;
		count++;
	}
	return (range);
}
