/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:17:46 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/08 17:00:41 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		counter;
	char	*newstr;

	counter = 0;
	newstr = (char *)malloc(sizeof(newstr) * ft_strlen(s) + 1);
	if (newstr == 0)
		return (NULL);
	while (s[counter] != '\0')
	{
		newstr[counter] = f(s[counter]);
		counter++;
	}
	return (newstr);
}
