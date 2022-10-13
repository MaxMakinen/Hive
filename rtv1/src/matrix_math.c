/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:06:19 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/24 14:45:37 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3f	mult_vec_matrix(t_vec3f vec, t_mat44f matrix)
{
	t_vec3f	new_vec;
	double	w;

	new_vec.x = vec.x * matrix.right.x + vec.y * matrix.up.x + \
	vec.z * matrix.forward.x + matrix.translate.x;
	new_vec.y = vec.x * matrix.right.y + vec.y * matrix.up.y + \
	vec.z * matrix.forward.y + matrix.translate.y;
	new_vec.z = vec.x * matrix.right.z + vec.y * matrix.up.z + \
	vec.z * matrix.forward.z + matrix.translate.z;
	w = vec.x * matrix.right.w + vec.y * matrix.up.w + vec.z * \
	matrix.forward.w + matrix.translate.w;
	new_vec = vec_div(new_vec, w);
	return (new_vec);
}

t_vec3f	mult_dir_matrix(t_vec3f vec, t_mat44f matrix)
{
	t_vec3f	new_dir;

	new_dir.x = vec.x * matrix.right.x + vec.y * matrix.up.x + \
	vec.z * matrix.forward.x;
	new_dir.y = vec.x * matrix.right.y + vec.y * matrix.up.y + \
	vec.z * matrix.forward.y;
	new_dir.z = vec.x * matrix.right.z + vec.y * matrix.up.z + \
	vec.z * matrix.forward.z;
	return (new_dir);
}

t_mat44f	invert_look_at(t_mat44f look)
{
	t_mat44f	matrix;

	matrix.forward.x = look.forward.x;
	matrix.forward.y = look.right.x;
	matrix.forward.z = look.up.x;
	matrix.right.x = look.forward.y;
	matrix.right.y = look.right.y;
	matrix.right.z = look.up.y;
	matrix.up.x = look.forward.z;
	matrix.up.y = look.right.z;
	matrix.up.z = look.up.z;
	matrix.translate.x = -(dot_product(matrix.translate, look.forward));
	matrix.translate.y = -(dot_product(matrix.translate, look.rigth));
	matrix.translate.z = -(dot_product(matrix.translate, look.up));
	return (matrix);
}

t_mat44f	look_at(t_vec3f from, t_vec3f to, t_vec3f up)
{
	t_mat44f	matrix;
	t_vec3f		forward;
	t_vec3f		right;
	t_vec3f		new_up;

	forward = normalize(vec_minus(from, to));
	right = normalize(cross_product(up, forward));
	new_up = normalize(cross_product(forward, right));
	matrix.forward = (t_vec4f){forward, 0};
	matrix.right = (t_vec4f){right, 0};
	matrix.up = (t_vec4f){newup, 0};
	matrix.from = (t_vec4f){from, 1};
	return (matrix);
}
