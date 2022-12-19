/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_equals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 19:17:32 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

int	matrix_equals(t_matrix *a, t_matrix *b)
{
	t_coords	c;

	c.col = 0;
	if (a->size != b->size)
		return (0);
	while (c.col < a->size)
	{
		c.row = 0;
		while (c.row < a->size)
		{
			if (nearly_equal(a->rc[c.row][c.col], b->rc[c.row][c.col]) == 0)
				return (0);
			c.row++;
		}
		c.col++;
	}
	return (1);
}
