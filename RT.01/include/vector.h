/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:30:57 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/13 15:31:02 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3i
{
	int	x;
	int	y;
	int	z;
}	t_vec3i;

typedef struct s_vec3f
{
	double	x;
	double	y;
	double	z;
}	t_vec3f;

typedef struct s_vec2f
{
	double	u;
	double	v;
}	t_vec2f;

t_vec3f	vec_mult(t_vec3f vec1, double mult);
t_vec3f	vec_div(t_vec3f vec, double div);
t_vec3f	vec_minus(t_vec3f vec1, t_vec3f vec2);
t_vec3f	vec_plus(t_vec3f vec1, t_vec3f vec2);
t_vec3f	cross_product(t_vec3f vec1, t_vec3f vec2);
t_vec3f	normalize(t_vec3f vec);
t_vec3f	unit_vec(t_vec3f vec);
double	vec_len(t_vec3f vec);
double	dot_product(t_vec3f vec1, t_vec3f vec2);
int		vec_compare(t_vec3f vec1, t_vec3f vec2);
t_vec3f	vec_invert(t_vec3f vec);
t_vec3f	vec_times(t_vec3f vec1, t_vec3f vec2);
t_vec3f	reflect_ray(t_vec3f ray, t_vec3f normal);
t_vec3f	get_vector(t_vec3f vector, char **words);

#endif
