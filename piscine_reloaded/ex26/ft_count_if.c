/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:41:08 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/03 13:49:53 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_if(char **tab, int(*f)(char*))
{
	int	counter;
	int	answer;

	answer = 0;
	counter = 0;
	while (tab[counter] != 0)
	{
		if (f(tab[counter]) == 1)
			answer++;
		counter++;
	}
	return (answer);
}
