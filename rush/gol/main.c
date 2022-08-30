/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:42 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/22 15:10:37 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char	*prep_map(char *filename)
{
	int		fd = open(filename, O_RDONLY);
	int		col = 0;
	int		row = 0;
	int		first = 1;
	char	*map;
	char	c;

	while(read(fd, &c, 1) != -1)
	{
		if (c == '\n')
		{
			row++;
			first = 0;
		}
		if (first = 1)
			col++;
		if (c == '\0')
			break;
	}
	map = (char *)malloc((col * row) + row);
	close(fd);
	fd = open(filename, O_RDONLY);
	map = read_map(fd, map);
	return (map);
}

char	*read_map(int fd, char *map)
{
	char	c;
	char	*write = map;

	while(read(fd, &c, 1) != -1)
	{
		if (c == '.')
		{
			a
			*write &= ~(1);
			*write << 1;
		}
		if (c == 'x')
		{
			*write &= 1;
			*write << 1;
		}
	}
}

int	main(int ac, char **av)
{
	int		fd = 0;
	char	*map;
	//TODO Make struct for line len info etc?
	if (ac == 3)
	{
		map = prep_map(av[1]);
		
