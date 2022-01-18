/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:35:25 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/14 15:25:32 by mmakinen         ###   ########.fr       */
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
		ft_putnbr(test);
		if (test > 0)
		{
			ft_putstr(" - ");
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
		ft_putnbr(test);
		if (test > 0)
		{
			ft_putstr(" - ");
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
		ft_putnbr(test);
		if (test > 0)
		{
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
		ft_putnbr(test);
		if (test > 0)
		{
			ft_putstr(" - ");
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
		ft_putnbr(test);
		if (test > 0)
		{
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
		ft_putnbr(test);
		if (test > 0)
		{
			ft_putstr(" - ");
			ft_putstr(line);
			ft_putchar('\n');
			free(line);
		}
	}
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
		ft_putnbr(test);
		if (test > 0)
		{
			ft_putstr(" - ");
			ft_putstr(line);
			ft_putchar('\n');
			free(line);
		}
	}
	close(fd);
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
		ft_putnbr(test);
		if (test > 0)
		{
			ft_putstr(" - ");
			ft_putstr(line);
			ft_putchar('\n');
			free(line);
		}
	}
	close(fd);
	ft_putchar('\n');
/*	ft_putstr("\n - Binary test 2 - \n");
	filename = "bin_test2.txt";

    FILE* output_file = fopen(filename, "wb+");
    if (!output_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fwrite(data, 1, sizeof(data), output_file);
//  printf("Done Writing!\n");
    fclose(output_file);

    FILE* in_file = fopen(filename, "rb");
    if (!in_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char* file_contents = malloc(sb.st_size);
    fread(file_contents, sb.st_size, 1, in_file);

    printf("read data: %s\n", file_contents);
    fclose(in_file);

    free(file_contents);
*/
	ft_putstr("\n -*- \n\n");
	filename = "bigass.txt";
	fd = open(filename, O_RDONLY);
	ft_putnbr(fd);
	ft_putchar('\n');
	test = 1;
	count = 1;
	while (test > 0)
	{
		test = get_next_line(fd, &line);
//		ft_putnbr(test);
//		ft_putstr(" | ");
		if (test > 0)
		{
//			ft_putnbr(count++);
//			ft_putstr(" - ");
//			ft_putstr(line);
//			ft_putchar('\n');
			free(line);
		}
	}
	close(fd);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("\n - just newline test - \n");
	filename = "nl.txt";
	fd = open(filename, O_RDONLY);
	test = 1;
	while (test > 0)
	{
		test = get_next_line(fd, &line);
		ft_putnbr(test);
		if (test > 0)
		{
			ft_putstr(" - ");
			if (!*line)
				ft_putstr("!*line\n");
			if (!line)
				ft_putstr("!line\n");
			ft_putstr(line);
			ft_putchar('\n');
			free(line);
		}
	}
	close(fd);
	ft_putchar('\n');
	ft_putstr("\n - bad filename test - \n");
	filename = "carp.txt";
	fd = open(filename, O_RDONLY);
	test = 1;
	while (test > 0)
	{
		test = get_next_line(fd, &line);
		ft_putnbr(test);
		if (test > 0)
		{
			ft_putstr(" - ");
			ft_putstr(line);
			ft_putchar('\n');
			free(line);
		}
	}
	ft_putchar('\n');
	ft_putstr("\n - bad fd test - \n");
	fd = 42;
	test = 1;
	while (test > 0)
	{
		test = get_next_line(fd, &line);
		ft_putnbr(test);
		if (test > 0)
		{
			ft_putstr(" - ");
			ft_putstr(line);
			ft_putchar('\n');
			free(line);
		}
	}
	ft_putchar('\n');
	ft_putstr("\n -*- \n\n");
	filename = "test_long.txt";
	fd = open(filename, O_RDONLY);
	test = 1;
	int mlem = 0;
	printf("file : %s\n",filename);
	while (test > 0)
	{
		test = get_next_line(fd, &line);
//		ft_putnbr(test);
		if (test > 0)
		{
//			ft_putstr(" - ");
//			ft_putstr(line);
//			ft_putchar('\n');
			free(line);
			mlem++;
		}
	}
	printf("lines : %i | should be : 32594\n", mlem);
	close(fd);
	ft_putstr("\n -*- \n\n");
	filename = "fillit.txt";
	fd = open(filename, O_RDONLY);
	test = 1;
	printf("file : %s\n",filename);
	while (test > 0)
	{
		test = get_next_line(fd, &line);
		ft_putnbr(test);
		if (test > 0)
		{
			ft_putstr(" - ");
			ft_putstr(line);
			ft_putchar('\n');
			free(line);
		}
	}
	close(fd);
	ft_putchar('\n');
	ft_putchar('\n');
	system("leaks GNL_test");
	ft_putchar('\n');
	return (0);
}
