/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_minor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 20:06:26 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

double	matrix_minor(t_matrix *m33, int skip_row, int skip_col)
{
	t_matrix	m22;
	double		determinant;

	m22 = matrix_submatrix(m33, (t_coords){skip_row, skip_col});
	determinant = matrix_determinant(&m22);
	return (determinant);
}
