/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:35:36 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/10 10:37:48 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		counter;
	char	*newstr;

	counter = 0;
	newstr = (char *)malloc(sizeof(newstr) * ft_strlen(s) + 1);
	if (newstr == 0)
		return (NULL);
	while (s[counter] != '\0')
	{
		newstr[counter] = f(counter, s[counter]);
		counter++;
	}
	return (newstr);
}
