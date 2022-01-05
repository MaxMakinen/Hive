/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:02:20 by oairola           #+#    #+#             */
/*   Updated: 2021/12/02 16:19:04 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s1_copy;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	if (len > n)
		s1_copy = (char *)malloc(sizeof(char) * (n + 1));
	else
		s1_copy = (char *)malloc(sizeof(char) * (len + 1));
	if (s1_copy == NULL)
		return (NULL);
	while (s1[i] != '\0' && i < n)
	{
		s1_copy[i] = s1[i];
		i++;
	}
	s1_copy[i] = '\0';
	return (s1_copy);
}
