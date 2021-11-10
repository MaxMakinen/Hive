/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:54:09 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/08 15:23:25 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	counter;

	counter = 0;
	newstr = (char *)malloc(sizeof(newstr) * len + 1);
	if (newstr == 0)
		return (NULL);
	while (counter < len)
	{
		newstr[counter] = s[start + counter];
		counter++;
	}
	newstr[counter] = '\0';
	return (newstr);
}
