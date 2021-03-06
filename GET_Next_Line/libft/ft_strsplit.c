/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:13:56 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/20 14:37:33 by mmakinen         ###   ########.fr       */
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

static char	*writer(char *arr, char const *s, char c, int *pos)
{
	int		symbol;
	int		position;

	position = *pos;
	symbol = 0;
	while (s[position] != c && s[position] != '\0')
		arr[symbol++] = s[position++];
	arr[symbol] = '\0';
	*pos = position;
	return (arr);
}

static void	*arr_free(char **arr)
{
	while (*arr != 0)
	{
		free(*arr);
		*arr++ = NULL;
	}
	return (NULL);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		pos;
	int		w_count;

	if (s == 0)
		return (NULL);
	w_count = 0;
	pos = 0;
	arr = (char **)malloc(sizeof(*arr) * (wordcount(s, c) + 1));
	if (arr == 0)
		return (NULL);
	while (s[pos] != '\0')
	{
		while (s[pos] == c)
			pos++;
		if (s[pos] != '\0')
		{
			arr[w_count] = ft_strnew(wordlen(s, c, pos) + 1);
			if (arr[w_count] == 0)
				return (arr_free(arr));
			writer(arr[w_count++], s, c, &pos);
		}
	}
	arr[w_count] = 0;
	return (arr);
}
