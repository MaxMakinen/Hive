/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:55:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/18 15:11:16 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
function to turn shape_id to binary
*/
unsigned long long	binary(unsigned short num)
{
	if (num == 0)
		return (0);
	if (num == 1)
		return (1);
	return (num % 2) + 10 * binary(num/2);
}

/*
Function to check for errors in file. Closes file at end to reset file offset, to be opened again in later.
*/

int check_file(int fd)
{
	int		ret;
	char	str[27];

	ret = read(fd, str, 26);
	while (ret >= 26)
		ret = read(fd, str, 26);
	str[ret] = 0;
	if (str[ret - 1] == '\n' && str[ret - 2] == '\n')
		return (-1);
	if (close(fd) == -1)
		return (-1);
	return (1);
}


int	main(int argc, char **argv)
{
	int	 	fd;
	t_tetro *head;

	if (argc != 2)
	{
		ft_putendl("usage: ./fillit filename");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putendl("error");
		return (1);
	}
/*	if (check_file(fd) == -1){
	ft_putendl("Check_file error");
		return (1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
*/	head = input(fd);
	if (!head)
	{
		if (close(fd) == -1)
		{
			ft_putendl("error");
			return (1);
		}
		ft_putendl("error");
		return (1);
	}
	if (close(fd) == -1)
	{
		ft_putendl("error");
		return (1);
	}
	while (head->next)
	{
		ft_putnbr(head->shape_id);
		ft_putstr("\n");
		ft_putchar(head->letter);
		ft_putchar('\n');
		head = head->next;
	}
	ft_putnbr(head->shape_id);
	ft_putstr("\n");
	ft_putchar(head->letter);
	ft_putchar('\n');
	return (0);
}

