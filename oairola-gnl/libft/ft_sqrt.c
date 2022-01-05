/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:12:35 by oairola           #+#    #+#             */
/*   Updated: 2021/11/29 13:43:56 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	count;
	int	odd;

	odd = 1;
	count = 0;
	if (nb < 1)
		return (0);
	if (nb == 1)
		return (1);
	while (nb != 0)
	{
		if (nb < 0)
			return (0);
		nb = nb - odd;
		odd = odd + 2;
		count++;
	}
	return (count);
}
