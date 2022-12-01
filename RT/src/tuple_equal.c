/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_equal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 16:31:31 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

int	tuples_equal(t_tuple a, t_tuple b)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (nearly_equal(a.a[i], b.a[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
