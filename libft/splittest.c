/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splittest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:00:03 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/05 17:12:39 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(void)
{
	char	*str = "**eat*my*********shorts*****banana***";
	char ** arr;
	char	d;
	int		c1 = 0;
//	int		c2 = 0;

	d = '*';
	arr = ft_strsplit(str, d);
	while (arr[c1] != '\0')
	{
		ft_putstr(arr[c1]);
		ft_putchar('\n');
		c1++;
	}
	return (0);
}
