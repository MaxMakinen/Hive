/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:44:03 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/13 09:48:19 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include <printf.h>
#include <stdio.h>

void	tuple_print(t_tuple t)
{
	printf("%5.5f %5.5f %5.5f %5.1f\n",
		t.s_xyzw.x,
		t.s_xyzw.y,
		t.s_xyzw.z,
		t.s_xyzw.w);
}
