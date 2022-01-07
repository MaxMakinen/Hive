/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strclr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:53:01 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/07 13:52:34 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int main (int argc, char **argv)
{
	char *mlem;
	if (argc > 2)
	{
		ft_putstr("give one string\n");
		return (1);
	}
	printf("	-=[strclr test]=-\n\n");
	if (argc == 1)
		mlem = ft_strdup("Sweet lord have mercy!");
	else
		mlem = argv[1];
	ft_putstr(mlem);
	ft_putstr(": END\n");
	ft_strclr(mlem);
	printf("%s",mlem);
	ft_putstr(": END\n\n");
	return (0);
}
