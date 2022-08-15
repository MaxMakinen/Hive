/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:06:19 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/10 10:10:32 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec4f	matrix_mult(t_vec4f m1, t_vec4f m2)
{
	t_vec4f	answer;
	int		x;
	int		y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			answer [y][x] = m1[y][0] * m2[0][x] + \
							m1[y][1] * m2[1][x] + \
							m1[y][2] * m2[2][x] + \
							m1[y][3] * m2[3][x];
			x++;
		}
		y++;
	}
	return (answer);
}
