/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:04:57 by oairola           #+#    #+#             */
/*   Updated: 2021/12/13 09:47:22 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static void	array_freer(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**looper(int d, char const *s, char c, char **array)
{
	int	a;
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		a = 0;
		array[d] = (char *)malloc(sizeof(char) * ft_wordlen(&s[i], c) + 1);
		if (array[d] == NULL)
		{
			array_freer(array);
			return (NULL);
		}
		while (s[i] != c && s[i] != '\0')
		{
			array[d][a++] = s[i++];
		}
		if (a != 0)
			array[d++][a] = '\0';
		while (s[i] == c && s[i])
			i++;
	}
	array[d] = NULL;
	return (array);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		d;

	d = 0;
	array = (char **)malloc(sizeof(char *) * ft_wordcount(s, c) + 1);
	if (array == NULL)
	{
		free(array);
		return (NULL);
	}
	return (looper(d, s, c, array));
}
