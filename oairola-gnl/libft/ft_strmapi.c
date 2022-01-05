/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:15:41 by oairola           #+#    #+#             */
/*   Updated: 2021/12/13 09:41:54 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*freshhh;
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	freshhh = (char *)malloc(sizeof(char) * i + 1);
	if (freshhh == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		freshhh[i] = f(i, s[i]);
		i++;
	}
	freshhh[i] = '\0';
	return (freshhh);
}
