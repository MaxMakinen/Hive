/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:33:47 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/13 15:33:51 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# include "rtv1.h"

typedef struct s_quaternion
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_quat;

void	quat_init(t_quat *quat);
double	quat_len(t_quat *q);
t_quat	quat_normalize(t_quat *q);
t_quat	quat_conjugate(t_quat *q);
void	quat_from_axis_angle(t_vec3f *axis, double angle, t_quat *quat);
void	quat_rotate(t_quat *quat, t_vec3f *point, t_vec3f *output);
void	quat_multiply(t_quat *q1, t_quat *q2, t_quat *output);

#endif
