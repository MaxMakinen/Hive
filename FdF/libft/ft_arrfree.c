/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 10:04:49 by mmakinen          #+#    #+#             */
/*   Updated: 2022/04/28 17:59:43 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_arrfree(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_strdel(&arr[i++]);
	}
	ft_strdel(arr);
	return (NULL);
}
