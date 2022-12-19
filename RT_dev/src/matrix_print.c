/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 20:12:19 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "rt.h"

void	matrix_print(t_matrix *mm)
{
	t_coords	c;

	printf("    0  1  2  3\n\n");
	c.row = 0;
	while (c.row < mm->size)
	{
		printf("%zu: ", c.row);
		c.col = 0;
		while (c.col < mm->size)
		{
			printf("%7.5f ", mm->rc[c.row][c.col]);
			c.col++;
		}
		printf("\n");
		c.row++;
	}
	printf("\n");
}
