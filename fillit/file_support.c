/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:58:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/19 13:02:06 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
