/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:42:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/07 14:21:15 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	capitalise(char c)
{
	return((char)ft_toupper(c));
}

void	cap(char *c)
{
	*c = ft_toupper(*c);
}

int main (int argc, char **argv)
{
	if (argc > 2)
	{
		ft_putstr("Give one string");
		return (1);
	}
	char	*mlem;
	if (argc == 1)
		mlem = ft_strdup("holy mackerel batman!");
	else
		mlem = argv[1];
	printf("	-=[strmap test]=-\n\n");
	printf("original : %s\n", mlem);
	ft_putstr("ft_strmap & ft_toupper	: ");
	ft_putstr(ft_strmap(mlem, capitalise));
	ft_putchar('\n');
	ft_putstr("ft_striter & ft_toupper	: ");
	ft_striter(mlem, cap);
	printf("%s\n",mlem);
	ft_putchar('\n');
	return (0);
}

