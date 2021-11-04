/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:01:49 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/02 16:22:05 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);

int	ft_strcmp(char *s1, char *s2)
{
	int	counter;

	counter = 0;
	while (s1[counter] != '\0' || s2[counter] != '\0')
	{
		if (s1[counter] > s2[counter])
			return (1);
		if (s1[counter] < s2[counter])
			return (-1);
		counter++;
	}
	return (0);
}

void	ft_sort_params(int argc, char **argv)
{
	int		counter;
	int		counter2;
	char	*save;

	counter = 1;
	counter2 = 1;
	while (counter < argc)
	{
		counter2 = counter + 1;
		while (counter2 < argc)
		{
			if (ft_strcmp(argv[counter], argv[counter2]) > 0)
			{
				save = argv[counter];
				argv[counter] = argv[counter2];
				argv[counter2] = save;
			}
			counter2++;
		}
		counter++;
	}
}

void	ft_print(char *str)
{
	int	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		ft_putchar (str[counter]);
		counter++;
	}
	ft_putchar ('\n');
}

int	main(int argc, char **argv)
{
	int	counter;

	counter = 1;
	ft_sort_params(argc, argv);
	while (counter < argc)
	{
		ft_print(argv[counter]);
		counter++;
	}
	return (0);
}
