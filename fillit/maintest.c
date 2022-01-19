/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:55:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/19 12:16:41 by mmakinen         ###   ########.fr       */
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
	return ((num % 2) + 10 * binary(num / 2));
}

/*
Function to open a file and return the fd.
In case of error it will print "error\n" into stdout and exit with 0.
*/

int	open_fd(char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
		ft_putendl("error");
	return (*fd);
}

/*
Function to close an open fd.
In case of error it will print "error\n" into stdout and exit with 0.
*/

int	close_fd(int fd)
{
	if (close(fd) == -1)
	{
		ft_putendl("error");
		return (0);
	}
	return (1);
}

/*
function to print out the usage of program in case of incorrect amount of input.
*/

int	print_usage(void)
{
	ft_putendl("usage: ./fillit filename");
	return (0);
}

/*
function that prints out "error\n" into stdout. Returns number to exit main with.
*/

int	error(int err)
{
	ft_putendl("error");
	return (err);
}

/*
Example for building and testing main.
*/

int	main(int argc, char **argv)
{
	int		fd;
	t_tetro	*head;

	if (argc != 2)
		return (print_usage());
	if (open_fd(argv[1], &fd) == -1)
		return (1);
	head = input(fd);
	if (close_fd(fd) == -1)
		return (2);
	if (!head)
		return (error(3));
/*mmakinen tests. Prints out content of struct list*/
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
