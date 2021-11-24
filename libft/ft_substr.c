/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:54:09 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/24 18:25:13 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	counter;

	counter = 0;
	if (s == 0)
		return (NULL);
	newstr = ft_strnew(len);
	if (newstr == 0)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (counter < len)
		{
			newstr[counter] = s[start + counter];
			counter++;
		}
	}
	newstr[counter] = '\0';
	return (newstr);
}
