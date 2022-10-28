/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:39:38 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/17 18:33:50 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "rt.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);

t_vec3	multiply_vectors(t_vec3 a, t_vec3 b);
t_vec3	div_vectors(t_vec3 a, t_vec3 b);

t_vec3	multiply_vect_float(t_vec3 a, double b);
t_vec3	div_vect_float(t_vec3 a, double b);
t_vec3	add_vect_float(t_vec3 a, double b);

double	vec3_sqr(t_vec3 a);
double	vec3_mag(t_vec3 u);
t_vec3	vec3_unit(t_vec3 u);
t_vec3	vec3_scalar_mult(t_vec3 u, double x);
t_vec3	vec3_neg(t_vec3 u);

#endif