/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:31:48 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/12 14:32:36 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"
/*
move following includes and struct into libft.h
*/
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
DELETE THESE! FOR TESTING ONLY!
*/
#include <stdio.h>

/*
struct to contain amount and formula of all 19 fixed tetrominos.
we need an int string with total sum, sum of n1, sum n2, sum n3, sum n4.
Or do we just always calculate it? so total sum + formulas?

typedef struct	s_tetrominos
{
	int		tetrominos[19];
	int		t0 = x+(x+1)+(x+w+1)+(x+w+w+1)
//should we use these per tetromino after all? every one found in input gets its own linked list node?
//same nodes could be used to store their positions in solution.
}				t_tetrominos
*/

/*
Function to return information about tetromino fir identification purposes. Inverted L.
	##
	 #
	 #
*/
int	*tetromino(int topleft, int width)
{
	int	*tet_data;
	int	i;

	tet_data = (int	*)malloc(sizeof(int) * 5);
	i = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + 1;
	tet_data[3] = topleft + width + 1;
	tet_data[4] = topleft + width + width + 1;
	while (i < 5)
		tet_data[0] += tet_data[i++];
	return (tet_data);
}

/*
Identify tetromino by comparing total sum of "full" squares.
*/

int identify(int total, int topleft, int **tet_pieces)
{
	int	*compare;
	int width = 5;

	compare = tetromino(topleft, width);
	if (total == *compare)
	{
		*tet_pieces = compare;
		return (1);
	}

/*	if (total == t0(topleft, width)
		return (*tet_pieces[0] += 1); // need a function for assigning value to array and return 1 on success. 
*/	return (-1);
}

//What if topleft is always 1? ignore it's actual value. then to compare we'd have all known sums of tetros.

/*
Function to count hashes from input to find tetrominos
*/

int counthashes(char *line, int *topleft, int rows)
{
	int	index;
	int	total;
	int width =  5;
	
	index = 0;
	total = 0;
	while (line[index])
	{
		if (line[index] == '#')
		{
			if (*topleft == 0)
				*topleft = (index + 1 + ((rows - 1) * width));
			total += (index + 1 + ((rows -1) * width));
		}
		index++;
	}
	return (total);
}

/*
Opens file and uses get_next_line to read lines from input file while checking that input is in correct format.
Sends input over to identifier to identify tetromino.
*/

int	input(int fd, int **tet_pieces)
{
	int		check;
	int		topleft;
	int		test;
	size_t	rows;
	int		total;
	char	*line;
	
	check = 1;
	topleft = 0;
	total = 0;
	check = get_next_line(fd, &line);
	rows = 1;
//	printf("check = %i\n	line = %s\nrow = %li\n", check, line, rows);
	while (check > 0)
	{
		if (ft_strlen(line) != 5 && rows != 5)
		{
			printf("ft_strlen check failed\nft_strlen = %li\nrow = %li\n", ft_strlen(line), rows);
			return (-1);
		}
		if (!ft_strlen(line))
		{
			if(rows > 5)
			{
				printf("too many rows\n");
				return (-1);
			}
			if (rows == 5)
			{
				test = identify(total, topleft, tet_pieces);
				if (test == -1)
				{
					printf("identify failed\n");
					return (-1);
				}
				rows = 0;
				total = 0;
				topleft = 0;
			}
		}
		if (rows > 5)
			return (-1);
		total += counthashes(line, &topleft, rows);
		check = get_next_line(fd, &line);
		rows++;
//		printf("\t\ttotal = %i\n", total);
//		printf("check = %i\n	line = %s\nrow = %li\n", check, line, rows);
	}
	return (1);
}

/*
Temp main for testing purposes. And to help me visualise how the input function will interact with the main.
*/

int main(int argc, char **argv)
{
	int	fd;
	int	*tet_pieces;
	int list[19];

	if (argc != 2)
	{
		ft_putstr("Feed me a file! a tetromino file!\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Open failed\n");
		return (-1);
	}
	input(fd, &tet_pieces);
	if (close(fd) == -1)
		printf("Close failed\n");
	int i = 0;
	while (i < 5)
	{
		printf("i = %i	content = %i\n", i, tet_pieces[i]);
		i++;
	}
	printf("total 0 =	%i\n", tet0(1,5));
	printf("total 1 =	%i\n", tet1(1,5));
	printf("total 2 =	%i\n", tet2(1,5));
	printf("total 3 =	%i\n", tet3(1,5));
	printf("total 4 =	%i\n", tet4(1,5));
	printf("total 5 =	%i\n", tet5(1,5));
	printf("total 6 =	%i\n", tet6(1,5));
	printf("total 7 =	%i\n", tet7(1,5));
	printf("total 8 =	%i\n", tet8(1,5));
	printf("total 9 =	%i\n", tet9(1,5));
	printf("total 10 =	%i\n", tet10(1,5));
	printf("total 11 =	%i\n", tet11(1,5));
	printf("total 12 =	%i\n", tet12(1,5));
	printf("total 13 =	%i\n", tet13(1,5));
	printf("total 14 =	%i\n", tet14(1,5));
	printf("total 15 =	%i\n", tet15(1,5));
	printf("total 16 =	%i\n", tet16(1,5));
	printf("total 17 =	%i\n", tet17(1,5));
	printf("total 18 =	%i\n", tet18(1,5));
	
	return (0);
}
