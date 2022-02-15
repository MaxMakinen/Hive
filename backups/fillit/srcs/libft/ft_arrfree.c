/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 10:04:49 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/04 10:10:38 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_arrfree(char **arr)
{
	char	*temp;

	while (*arr)
	{
		temp = *arr++;
		ft_strdel(&temp);
	}
	ft_strdel(arr);
	return (NULL);
}
