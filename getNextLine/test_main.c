/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:35:25 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/21 12:50:10 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/stat.h>

int	main(void)
{
	int		fd;
	char	*line;
	char	*filename;
	int		test;
	size_t	count;

	filename = "lorem.txt";
	fd = open(filename, O_RDONLY);
	ft_putnbr(fd);
	ft_putchar('\n');
	test = 1;
	count = 0;
	while (test > 0 && count < 2)
	{
		test = get_next_line(fd, &line);
		if (test > 0)
		{
			ft_putstr(line);
			free(line);
			ft_putchar('\n');
		}
		count++;
	}
//	close(fd);
	ft_putchar('\n');
	ft_putstr("\n -*- \n\n");
	filename = "lorum.txt";
	fd = open(filename, O_RDONLY);
	test = 1;
	ft_putnbr(fd);
	ft_putchar('\n');
	while (test > 0)
	{
		test = get_next_line(fd, &line);
		if (test > 0)
		{
			ft_putstr(line);
			free(line);
			ft_putchar('\n');
		}
	}
//	close(fd);
	ft_putchar('\n');
	ft_putstr("\n -*- \n\n");
	filename = "gnl1_1.txt";
	fd = open(filename, O_RDONLY);
	ft_putnbr(fd);
	ft_putchar('\n');
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
			free(line);
		}
	}
//	close(fd);
	ft_putchar('\n');
	ft_putstr("\n -*- \n\n");
	ft_putnbr(3);
	ft_putchar('\n');
	test = 1;
	while (test > 0)
	{
		test = get_next_line((3), &line);
		if (test > 0)
		{
			ft_putstr(line);
			free(line);
			ft_putchar('\n');
		}
		count++;
	}
	ft_putchar('\n');
	ft_putstr("\n -*- \n\n");
	filename = "gnl7_3.txt";
	fd = open(filename, O_RDONLY);
	ft_putnbr(fd);
	ft_putchar('\n');
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
			free(line);
		}
	}
//	close(fd);
	ft_putchar('\n');
	ft_putstr("\n -*- \n\n");
	filename = "gnl7_2.txt";
	fd = open(filename, O_RDONLY);
	ft_putnbr(fd);
	ft_putchar('\n');
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
			free(line);
		}
	}
	ft_putchar('\n');
	ft_putstr("\n -*- \n\n");
	filename = "gnl7_3.txt";
	fd = open(filename, O_RDONLY);
	ft_putnbr(fd);
	ft_putchar('\n');
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
			free(line);
		}
	}
//	close(fd);
	ft_putchar('\n');
	ft_putnbr(MAX_FD);
	ft_putchar('\n');
	while (fd > 2)
		close(fd--);
	ft_putstr("\n - Binary test - \n");
	FILE	*bin;
	const uint8_t data[] =
        { 0x54, 0x65, 0x6d, 0x70, 0x6f, 0x72, 0x61, 0x72, 0x79,
          0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x20, 0x74,
          0x6f, 0x20, 0x62, 0x65, 0x20, 0x77, 0x72, 0x69, 0x74,
          0x74, 0x65, 0x6e, 0x20, 0x74, 0x6f, 0x20, 0x66, 0x69,
          0x6c, 0x65 };

	filename = "bin_test.bin";
	bin = fopen(filename, "wb");
	fwrite (data , 1, sizeof(data), bin);
	fclose(bin);
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
			free(line);
		}
	}
	close(fd);
	ft_putchar('\n');
	return (0);
}
