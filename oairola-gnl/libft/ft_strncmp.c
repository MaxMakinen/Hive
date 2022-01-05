/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:46:11 by oairola           #+#    #+#             */
/*   Updated: 2021/11/29 14:17:37 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_copy;
	unsigned char	*s2_copy;

	s1_copy = (unsigned char *)s1;
	s2_copy = (unsigned char *)s2;
	i = 0;
	while (s1_copy[i] != '\0' && i < n)
	{
		if (s1_copy[i] != s2[i])
			return ((s1_copy[i] - s2_copy[i]));
		i++;
	}
	if (s2_copy[i] == '\0' || i == n)
		return (0);
	else
		return ((s1_copy[i] - s2_copy[i]));
	return (0);
}
