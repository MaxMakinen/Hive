/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:35:25 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/16 14:22:33 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main()
{
	int 	fd;
	char	*line;
	char	*filename;
	int		test;

	filename = "lorem.txt";
	fd = open(filename, O_RDONLY);
	test = 1;
	while (test > 0)
	{
		test = get_next_line(fd, &line);
		if (test > 0)
		{
			ft_putstr(line);
			ft_putchar('\n');
		}
	}
	close(fd);
	ft_putnbr(test);
	ft_putchar('\n');
	filename = "gnl7_2.txt";
	fd = open(filename, O_RDONLY);
	test = 1;
	while (test > 0)
	{
		test = get_next_line(fd, &line);
		if (test > 0)
		{
			ft_putnbr(test);
			ft_putstr(" - ");
			ft_putstr(line);
			ft_putchar('\n');
		}
	}
	close(fd);
	ft_putnbr(test);
	ft_putchar('\n');
	return (0);
}
