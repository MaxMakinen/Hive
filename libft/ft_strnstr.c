/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:04:48 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/19 11:12:59 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	char		*seeker;
	const char	*end;
	size_t		len;

	seeker = (char*)haystack;
	if (needle == 0)
		return (seeker);
	len = ft_strlen(needle);
	end = seeker + n;
	while (*seeker != '\0' && seeker != end)
	{
		if (ft_strncmp(seeker, needle, len) == 0)
			return (seeker);
		seeker++;
	}
	return (NULL);
}
