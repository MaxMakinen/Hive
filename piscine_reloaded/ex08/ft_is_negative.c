/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:37:13 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/03 15:15:18 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	ft_is_negative(int x)
{
	if (x < 0)
	{
		ft_putchar('N');
	}
	else
	{
		ft_putchar('P');
	}
}
