/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:13:56 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/04 10:14:45 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcount(char const *s, unsigned char c)
{
	int	count;
	int	test;
	int	w_count;

	test = 0;
	count = 0;
	w_count = 0;
	while (s[count] != '\0')
	{
		while (s[count] != c && s[count + 1] != '\0')
		{
			count++;
			test = 1;
		}
		while (s[count] == c || s[count + 1] == '\0')
		{
			w_count += test;
			test = 0;
			count++;
		}
	}
	return (w_count);
}

static int	wordlen(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s != c && *s)
	{
		count++;
		s++;
	}
	return (count);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**arr;
	char	**temp;
	size_t	w_count;

	if (!s)
		return (NULL);
	w_count = wordcount(s, (unsigned char)c);
	arr = (char **)ft_memalloc(sizeof(arr) * (w_count + 1));
	if (!arr)
		return (NULL);
	temp = arr;
	while (*s && w_count--)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			*temp = ft_strsub(s, 0, wordlen(s, c));
			if (!*temp++)
				return (ft_arrfree(arr));
			s += wordlen(s, c);
		}
	}
	return (arr);
}
