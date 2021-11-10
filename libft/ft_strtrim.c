/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:51:38 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/08 15:25:42 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	beginning(char const *s)
{
	int	pos;

	pos = 0;
	while (s[pos] != '\0')
	{
		if (s[pos] != '\n' && s[pos] != ' ' && s[pos] != '\t')
			return (pos);
		pos++;
	}
	return (0);
}

static int	ending(char const *s)
{
	int	pos;
	int	counter;

	pos = 0;
	counter = 0;
	while (s[pos] != '\0')
	{
		while (s[pos] == '\n' || s[pos] == '\t' || s[pos] == ' ')
		{
			counter++;
			pos++;
		}
		if (s[pos] == '\0')
			return (pos - counter);
		counter = 0;
		pos++;
	}
	return (pos);
}

char	*ft_strtrim(char const *s)
{
	char	*newstr;
	int		len;
	int		start;
	int		end;
	int		counter;

	counter = 0;
	start = beginning(s);
	end = ending(s);
	len = end - start;
	newstr = (char *)malloc(sizeof(newstr) * len);
	if (newstr == 0)
	{
		ft_putstr("malloc failed");
		return (NULL);
	}
	while (counter < len)
	{
		newstr[counter] = s[start + counter];
		counter++;
	}
	newstr[counter] = '\0';
	return (newstr);
}
