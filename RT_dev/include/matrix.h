/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:48:26 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/07 15:01:13 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H
# include "coords.h"
# include "tuple.h"
# include <stddef.h>

typedef struct s_matrix
{
	double	rc[4][4];
	size_t	size;
}			t_matrix;

t_matrix	matrix_new(size_t size);
void		matrix_print(t_matrix *mm);
t_tuple		matrix_tuple_multiply(t_matrix *m, t_tuple *t);
void		matrix_transpose(t_matrix *m);
double		matrix_determinant(t_matrix *m);
t_matrix	matrix_submatrix(t_matrix *src, t_coords c);
double		matrix_minor(t_matrix *m, int skip_row, int skip_col);
double		matrix_cofactor(t_matrix *m, int row, int col);
t_matrix	matrix_inverse(t_matrix *m);
t_matrix	matrix_translate(double x, double y, double z);
t_matrix	matrix_scale(double x, double y, double z);
t_matrix	matrix_rotate_x(double w);
t_matrix	matrix_rotate_y(double w);
t_matrix	matrix_rotate_z(double w);
int			matrix_equals(t_matrix *a, t_matrix *b);
t_matrix	matrix_multiply(t_matrix *a, t_matrix *b);
double		matrix_row_column_multiply(
				t_matrix *a,
				t_matrix *b,
				t_coords c);
t_matrix	matrix_new_identity(int size);

#endif