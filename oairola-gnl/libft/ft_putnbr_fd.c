/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:42:57 by oairola           #+#    #+#             */
/*   Updated: 2021/12/02 14:53:20 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putlongnbr_fd(long int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putlongnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putlongnbr_fd(n / 10, fd);
		ft_putlongnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	a;

	a = (long int)n;
	ft_putlongnbr_fd(a, fd);
}
