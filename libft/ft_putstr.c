/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:32:32 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/19 13:47:09 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *s)
{
	unsigned char	*uc;

	uc = (unsigned char *)s;
	if (s != NULL || s != 0)
	{
		
		write(1, uc, ft_strlen((const char *)uc) * sizeof(*uc));
	}
}
