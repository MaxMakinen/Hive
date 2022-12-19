/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tuple_multiply.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 19:50:17 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

static double	matrix_row_multiply(t_matrix *m, t_tuple *t, int row)
{
	size_t	col;
	double	result;

	col = 0;
	result = 0.0;
	while (col < m->size)
	{
		result += m->rc[row][col] * t->a[col];
		col++;
	}
	return (result);
}

t_tuple	matrix_tuple_multiply(t_matrix *m, t_tuple *t)
{
	t_tuple	result;
	int		i;

	i = 0;
	while (i < 4)
	{
		result.a[i] = matrix_row_multiply(m, t, i);
		i++;
	}
	return (result);
}
