/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:26:54 by oairola           #+#    #+#             */
/*   Updated: 2021/12/02 11:02:30 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_end(char const *s, int len)
{
	int	end;

	while (s[len] != '\0')
		len++;
	len--;
	while (s[len] == ' ' || s[len] == '\n' || s[len] == '\t')
		len--;
	end = len + 1;
	return (end);
}

static int	ft_start(char const *s)
{
	int	start;

	start = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	return (start);
}

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		len;
	int		start;
	int		end;

	len = ft_strlen(s);
	start = ft_start(s);
	end = ft_end(s, len);
	len = end - start;
	if (len < 0)
		len = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	len = 0;
	while (start < end)
	{
		str[len] = s[start];
		start++;
		len++;
	}
	str[len] = '\0';
	return (str);
}
