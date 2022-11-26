/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transpose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 19:53:50 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	matrix_transpose(t_matrix *m)
{
	double		temp;
	t_coords	c;

	c.row = 1;
	while (c.row < m->size)
	{
		c.col = 0;
		while (c.col < c.row)
		{
			temp = m->rc[c.row][c.col];
			m->rc[c.row][c.col] = m->rc[c.col][c.row];
			m->rc[c.col][c.row] = temp;
			c.col++;
		}
		c.row++;
	}
}
