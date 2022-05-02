/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:29:05 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/02 17:29:56 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_intvec get_delta(t_vector start, t_vector end)
{
	t_intvec	delta;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	delta.z = end.z - start.z;
	return (delta);
}

t_intvec abs_vector(t_intvec intvec)
{
	intvec.x = ft_abs(intvec.x);
	intvec.y = ft_abs(intvec.y);
	intvec.z = ft_abs(intvec.z);
	return (intvec);
}
