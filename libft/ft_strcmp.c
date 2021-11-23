/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:28:52 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/23 11:29:26 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char const *s1, char const *s2)
{
	int	count;

	count = 0;
	while ((s1[count] == s2[count]) && (s1 || s2))
	{
		count++;
	}
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}
