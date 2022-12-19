/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_row_column_multiply.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/07 15:04:59 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

double	matrix_row_column_multiply(
	t_matrix *a,
	t_matrix *b,
	t_coords c)
{
	size_t	i;
	double	result;

	i = 0;
	result = 0;
	if (a->size == b->size)
	{
		while (i < a->size)
		{
			result += a->rc[c.row][i] * b->rc[i][c.col];
			i++;
		}
	}
	return (result);
}
