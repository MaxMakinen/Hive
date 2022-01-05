/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:20:55 by oairola           #+#    #+#             */
/*   Updated: 2021/11/30 15:51:06 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wordcount(char const *s, char c)
{
	int	len;
	int	wordcount;

	wordcount = 0;
	len = 0;
	while (s[len] != '\0')
	{
		while (s[len] == c)
			len++;
		while (s[len] != c && s[len] != '\0')
			len++;
		wordcount++;
	}
	return (wordcount);
}
