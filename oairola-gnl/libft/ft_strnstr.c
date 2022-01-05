/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:15:34 by oairola           #+#    #+#             */
/*   Updated: 2021/12/07 14:10:45 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;
	size_t	start;
	size_t	start_save;
	size_t	i;

	start = 0;
	len_needle = ft_strlen(needle);
	if (len_needle == 0)
		return ((char *)haystack);
	while (haystack[start] != '\0' && start < len)
	{
		i = 0;
		start_save = start;
		while (haystack[start + i] == needle[i] && (start + i) < len)
		{
			i++;
			if (i == len_needle)
				return ((char *)&haystack[start_save]);
		}
		start++;
	}
	return (NULL);
}
