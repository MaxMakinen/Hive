/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:16:12 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/25 16:24:03 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int main(void)
{
	char    *data = "hello, i'm a data";
	t_list  *l = ft_lstnew(data, ft_strlen(data));
	
	write(2, "", 1);

	printf("$%s$ : $%s$\n", data, (char *)l->content);
	if (!ft_strcmp(data, l->content))
	{
		free(l);
		 printf("TEST_SUCCESS");
	}
	else
		printf("TEST_FAILED");
}

