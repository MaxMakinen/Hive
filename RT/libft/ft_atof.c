/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:03:32 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/22 19:20:06 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
/*
static double	get_desimal_div(int count)
{
	double	ret;

	ret = 1.0;
	while (count != 0)
	{
		ret *= 10;
		count--;
	}
	return (ret);
}
*/
double	ft_atof(char *line_arg_r)
{
	double	r;
	double	negative;

	negative = 1.0f;
	r = 0.0;
	if (*line_arg_r == '-')
	{
		negative = -1.0f;
		line_arg_r++;
	}
	int num = 0;
	int dec = 0;
	int len = 0;

	num = ft_atoi(line_arg_r);
	while (*line_arg_r != '\0' && *line_arg_r != '.')
		line_arg_r++;
	line_arg_r++;
	while (line_arg_r[len] != '\0' && ft_isdigit(line_arg_r[len]))
		len++;
	if (len)
	{
		dec = ft_atoi(line_arg_r);
		r = (double)(dec / powf(10, len));
	}
	return ((r + (double)num) * (double)negative);
}
