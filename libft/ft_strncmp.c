/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:52:06 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/08 16:01:07 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t	counter;

	counter = 0;
	while ((s1[counter] != '\0' || s2[counter] != '\0') && counter <= n)
	{
		if (s1[counter] > s2[counter])
			return (1);
		if (s1[counter] < s2[counter])
			return (-1);
		counter++;
	}
	return (0);
}
