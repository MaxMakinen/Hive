/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:46:15 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/10 12:01:54 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	int		count;

	count = 0;
	str = (char *)malloc(sizeof(str) * size + 1);
	if (str == 0)
		return (NULL);
	while (count <= size)
	{
		str[count] = '\0';
		count++;
	}
	str[count] = '\0';
	return (str);
}
