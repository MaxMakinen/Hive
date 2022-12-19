/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/15 12:48:44 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	matrix_determinant(t_matrix *m)
{
	size_t	i;
	double	result;

	if (m->size == 2)
		return (m->rc[0][0] * m->rc[1][1] - m->rc[0][1] * m->rc[1][0]);
	result = 0.0;
	i = 0;
	while (i < m->size)
	{
		result += m->rc[0][i] * matrix_cofactor(m, 0, i);
		i++;
	}
	return (result);
}
