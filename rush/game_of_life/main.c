/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:22:42 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/22 11:48:03 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char	*prep_map(char *filename))
{
	int	fd = open(filename, O_RDONLY);
	int len = 0;
	char *map;
	char c;

	while(read(fd, &c, 1) != -1)
	{
		if (c == '\n')
			break;
		if (c == '\0')
			return ("ERROR");
		len++;
	}
	map = (char *)malloc(len * len);
	close(fd);
	fd = open(filename, O_RDONLY);
	map = read_map(fd, map);
	return (map);
}

char	*read_map(int fd, char *map)
{
	char	c;
	char	*write = map;
	//TODO take input from fd and turn into binary map;
	while(read(fd, &c, 1) != -1)
	{
		if (c == '.')
		{
			*write &= ~(1);
			*write << 1;
		}
		if (c == 'x')
		{
			*write &= 1;
			*write << 1;
		}
//		if (c == '\n')
		}
}

int	main(int ac, char **av)
{
	int		fd = 0;
	char	*map;

	if (ac == 3)
	{
		map = prep_map(av[1]);
		
