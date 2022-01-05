/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:43:49 by oairola           #+#    #+#             */
/*   Updated: 2021/11/30 14:12:39 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1_copy;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	s1_copy = ft_strnew(len);
	if (s1_copy == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s1_copy[i] = s1[i];
		i++;
	}
	s1_copy[i] = '\0';
	return (s1_copy);
}
