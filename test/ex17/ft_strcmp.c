/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:01:23 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/02 12:14:38 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>

void tester(int x)
{
	if (x < 0)
		write(1,"n",1);
	if (x > 0)
		write(1,"p",1);
	if (x == 0)
		write(1,"s",1);
}


int	ft_strcmp(char *s1, char *s2)
{
	int counter;

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

int main (void)
{
	tester(ft_strcmp("banana","banana"));
	tester(ft_strcmp("banana","bonono"));
	tester(ft_strcmp("banana","ban"));
	tester(ft_strcmp("bonono","banana"));
	write(1,"\n\n",2);	
	tester(strcmp("banana","banana"));
	tester(strcmp("banana","bonono"));
	tester(strcmp("banana","ban"));
	tester(strcmp("bonono","banana"));
	return (0);
}
