/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:58:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/31 14:41:50 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
Function to open a file and return the fd.
In case of error it will print "error\n" into stdout and exit with 0.
*/

int	open_fd(char *filename, int *fd)
{
	if (!file_check(filename))
		error(3);
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
		error(3);
	return (*fd);
}

/*
Function to close an open fd.
In case of error it will print "error\n" into stdout and exit with 0.
*/

int	close_fd(int fd)
{
	if (close(fd) == -1)
		error(2);
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
	exit(err);
}

/*
function to check file length and last characters
*/

int	file_check(char *filename)
{
	int		fd;
	int		file_len;
	char	buffer[576];

	fd = open(filename, O_RDONLY);
	file_len = read(fd, buffer, 576);
	close_fd(fd);
	buffer[file_len] = 0;
	if (file_len > 545)
		return (0);
	if (buffer[file_len - 1] != '\n' || buffer[file_len - 2] == '\n')
		return (0);
	return (1);
}
