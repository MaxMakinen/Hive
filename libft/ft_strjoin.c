/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:53:37 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/24 12:00:40 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		len;
	int		count;

	count = 0;
	if (s1 == 0 || s2 == 0)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2));
	newstr = (char *)malloc(sizeof(*newstr) * len + 1);
	if (newstr == 0)
		return (NULL);
	while (s1[count] != '\0')
	{
		newstr[count] = s1[count];
		count++;
	}
	len = 0;
	while (s2[len] != '\0')
	{
		newstr[count] = s2[len];
		count++;
		len++;
	}
	newstr[count] = '\0';
	return (newstr);
}
