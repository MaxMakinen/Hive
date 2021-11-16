/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:41:58 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/15 14:44:22 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*memset(void *b, int c, size_t len)
{
	char	*copy;
	char	*end;

	copy = *b;
	end = copy + len;
	while (copy < end)
	{
		*copy++ = (unsigned char *)c;
	}
	return (b);
}
