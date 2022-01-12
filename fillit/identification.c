/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:53:24 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/11 17:31:00 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fillit.h"

/*
Tetromino 0
	##
	 #
	 #
*/

int	tet0(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + 1;
	tet_data[3] = topleft + width + 1;
	tet_data[4] = topleft + width + width + 1;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 1
	  #
	###
*/

int	tet1(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + width - 2;
	tet_data[3] = topleft + width - 1;
	tet_data[4] = topleft + width;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 2
	#
	#
	##
*/

int	tet2(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + width;
	tet_data[3] = topleft + width + width;
	tet_data[4] = topleft + width + width + 1;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 3
	###
	#
*/

int	tet3(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + 1;
	tet_data[3] = topleft + 2;
	tet_data[4] = topleft + width;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 4
	 #
	 #
	##
*/

int	tet4(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + width;
	tet_data[3] = topleft + width + width;
	tet_data[4] = topleft + width + width - 1;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 5
	###
	  #
*/

int	tet5(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + 1;
	tet_data[3] = topleft + 2;
	tet_data[4] = topleft + width + 2;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 6
	##
	#
	#
*/

int	tet6(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + 1;
	tet_data[3] = topleft + width;
	tet_data[4] = topleft + width + width;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 7
	#
	###
*/

int	tet7(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + width;
	tet_data[3] = topleft + width + 1;
	tet_data[4] = topleft + width + 2;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 8
	 ##
	##
*/

int	tet8(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + 1;
	tet_data[3] = topleft + width - 1;
	tet_data[4] = topleft + width;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 9
	#
	##
	 #
*/

int	tet9(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + width;
	tet_data[3] = topleft + width + 1;
	tet_data[4] = topleft + width + width + 1;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 10
	##
	 ##
*/

int	tet10(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + 1;
	tet_data[3] = topleft + width + 1;
	tet_data[4] = topleft + width + 2;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 11
	 #
	##
	#
*/

int	tet11(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + width - 1;
	tet_data[3] = topleft + width;
	tet_data[4] = topleft + width + width - 1;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 12
	###
	 #
*/

int	tet12(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + 1;
	tet_data[3] = topleft + 2;
	tet_data[4] = topleft + width + 1;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 13
	#
	##
	#
*/

int	tet13(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + width;
	tet_data[3] = topleft + width + 1;
	tet_data[4] = topleft + width + width;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 14
	 #
	###
*/

int	tet14(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + width - 1;
	tet_data[3] = topleft + width;
	tet_data[4] = topleft + width + 1;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 15
	 #
	##
	 #
*/

int	tet15(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + width - 1;
	tet_data[3] = topleft + width;
	tet_data[4] = topleft + width + width;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 16
	####
*/

int	tet16(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	width *= 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + 1;
	tet_data[3] = topleft + 2;
	tet_data[4] = topleft + 3;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 17
	#
	#
	#
	#
*/

int	tet17(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + width;
	tet_data[3] = topleft + width + width;
	tet_data[4] = topleft + width + width + width;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}

/*
Tetromino 18
	##
	##
*/

int	tet18(int topleft, int width)
{
	int	tet_data[5];
	int	index;

	//tet_data = (int *)malloc(sizeof(int) * width);
	index = 1;
	tet_data[0] = 0;
	tet_data[1] = topleft;
	tet_data[2] = topleft + 1;
	tet_data[3] = topleft + width;
	tet_data[4] = topleft + width + 1;
	while (index < 5)
		tet_data[0] += tet_data[index++];
	return (tet_data[0]);
}
