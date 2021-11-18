/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:41:58 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/18 11:48:35 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*memset(void *s, int c, size_t len)
{
	char	*copy;
	char	*end;

	copy = *s;
	end = copy + len;
	while (copy < end)
	{
		*copy++ = (unsigned char *)c;
	}
	return (s);
}
