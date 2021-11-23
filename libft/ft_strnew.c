/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:46:15 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/19 12:18:01 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	char	*strnew;
	char	*end;
	
	strnew = (char *)malloc(sizeof(str) * size + 1);
	if (strnew == 0)
		return (NULL);
	str = strnew;
	end = str + size;
	while (str <= end)
	{
		*str++ = '\0';
	}
	*str = '\0';
	return (strnew);
}
