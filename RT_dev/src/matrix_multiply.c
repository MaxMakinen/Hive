/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiply.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/07 15:07:21 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	matrix_multiply(t_matrix *a, t_matrix *b)
{
	t_coords	c;
	t_matrix	result;

	result = matrix_new(a->size);
	c.row = 0;
	if (a->size == b->size)
	{
		while (c.row < 4)
		{
			c.col = 0;
			while (c.col < 4)
			{
				result.rc[c.row][c.col] = matrix_row_column_multiply(a, b, c);
				c.col++;
			}
			c.row++;
		}
	}
	return (result);
}
