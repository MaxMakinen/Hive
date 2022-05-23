/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:40:44 by mmakinen          #+#    #+#             */
/*   Updated: 2022/05/23 09:07:42 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	zero_padding(const char *format, t_printf *data)
{
	data->flags = data->flags | ZERO;
	return (1);
}

int left_adjusted(const char *format, t_printf *data)
{
	data->flags = data->flags | LEFT;
	return (1);
}

int	add_plus(const char *format, t_printf *data)
{
	data->flags = data->flags | PLUS;
	return (1);
}

int	add_space(const char *format, t_printf *data)
{
	data->flags = data->flags | SPACE;
	return (1);
}

int add_prefix(const char *format, t_printf *data)
{
	data->flags = data->flags | PREFIX;
	return (1);
}
