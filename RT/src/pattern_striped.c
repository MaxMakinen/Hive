/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_striped.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:55:12 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/16 21:50:30 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	pattern_striped(double	coordinate_in)
{
	double	coordinate;
	double	floor_coordinate;

	coordinate = coordinate_in;
	floor_coordinate = (int)floor(coordinate);
	if (nearly_equal((coordinate - floor_coordinate), 0.0) == 1
		|| nearly_equal((coordinate - floor_coordinate), 1.0) == 1 )
		coordinate += 0.01;
	if ((((int)floor(coordinate)) % 2) == 0)
		return (1);
	return (0);
			
}