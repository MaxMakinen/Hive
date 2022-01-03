/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:54:29 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/05 11:46:56 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_display_file.h"
#include "libft.h"

int	errorcheck(int argc)
{
	if (argc == 1)
	{
		write(2, "File name missing.\n", 19);
		return (1);
	}
	if (argc > 2)
	{
		write(2, "Too many arguments.\n", 20);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		file_d;
	int		read_bytes;
	char	buffer[BUF_SIZE + 1];

	read_bytes = 1;
	if (errorcheck(argc) == 1)
		return (1);
	file_d = open(argv[1], O_RDWR | O_CREAT, 0666 );
	if (file_d == -1)
	{
		write(2, "open() failed.\n", 15);
		return (1);
	}

	ft_putstr_fd("Banana man enjoys kiwi juice. ", file_d);
	ft_putendl_fd("Pineapples are usually not airborne",  file_d);
	ft_putnbr_fd(20210511, file_d);
	ft_putchar_fd('\n', file_d);
	ft_putnbr_fd(-666, file_d);
	ft_putstr("Banana man enjoys kiwi juice. ");
	ft_putendl("Pineapples are usually not airborne");
	ft_putnbr(20210511);
	ft_putchar('\n');
	ft_putnbr(-666);

	while (read_bytes != 0)
	{
		read_bytes = read(file_d, buffer, BUF_SIZE);
		buffer[read_bytes] = '\0';
		write(1, &buffer, read_bytes);
	}
	if (close(file_d) == -1)
	{
		write(2, "close() failed.\n", 15);
		return (1);
	}
	return (0);
}
