/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:40:44 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/10 11:12:58 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	zero_padding(const char *format, t_printf *data)
{
	(void)format;
	data->flags = data->flags | ft_bit(ZERO);
	return (1);
}

int	left_adjusted(const char *format, t_printf *data)
{
	(void)format;
	data->flags = data->flags | ft_bit(LEFT);
	return (1);
}

int	add_plus(const char *format, t_printf *data)
{
	(void)format;
	data->flags = data->flags | ft_bit(PLUS);
	return (1);
}

int	add_space(const char *format, t_printf *data)
{
	(void)format;
	data->flags = data->flags | ft_bit(SPACE);
	return (1);
}

int	add_prefix(const char *format, t_printf *data)
{
	(void)format;
	data->flags = data->flags | ft_bit(PREFIX);
	return (1);
}
