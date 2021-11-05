/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:13:56 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/05 17:15:09 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char const *s, char c)
{
	int	count;
	int	test;
	int	w_count;

	test = 0;
	count = 0;
	w_count = 0;
	while (s[count] != c && s[count] != '\0')
	{
		count++;
		test = 1;
	}
	while (s[count] == c || s[count] == '\0')
	{
		w_count += test;
		test = 0;
		count++;
	}
	return (w_count);
}

static int	wordlen(char const *s, char c, int p)
{
	int	count;

	count = 0;
	while (s[p] != c && s[p] != '\0')
	{
		count++;
		p++;
	}
	return (count);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		pos;
	int		s_count;
	int		w_count;

	w_count = 0;
	pos = 0;
	if ((arr = (char **)malloc(sizeof(arr) * wordcount(s, c) + 1)) == 0)
		return (NULL);
	while (s[pos] != '\0')
	{
		while (s[pos] == c)
			pos++;
		if (s[pos] != '\0')
		{
			s_count = 0;
			if ((arr[w_count] = (char *)malloc(sizeof(arr) * wordlen(s, c, pos) + 1)) == 0)
				return (NULL);
			while (s[pos] != c && s[pos] != '\0')
				arr[w_count][s_count++] = s[pos++];
			arr[w_count++][s_count] = '\0';
		}
	}
	arr[w_count] = 0;
	return (arr);
}
