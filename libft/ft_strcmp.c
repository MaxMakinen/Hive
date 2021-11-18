/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:28:52 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/18 17:55:28 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char const *s1, char const *s2)
{
	int	count;

	count = 0;
	while (s1[count] == s2[count])
	{
		if (s1[count] == 0)
			return (0);
		if (s1[count] < s2[count])
			return (-1);
		count++;
	}
	return ((unsigned int)s1[count] - (unsigned int)s2[count]);
}
