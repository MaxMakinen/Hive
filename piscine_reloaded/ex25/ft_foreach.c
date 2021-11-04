/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:33:33 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/03 13:38:33 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_foreach(int *tab, int length, void(*f)(int))
{
	int	counter;

	counter = 0;
	while (counter < length)
	{
		f(tab[counter]);
		counter++;
	}
}
