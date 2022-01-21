/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:55:20 by mmakinen          #+#    #+#             */
/*   Updated: 2022/01/21 15:46:55 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
Example for building and testing main.
*/

int	main(int argc, char **argv)
{
	int		fd;
	t_tetro	*head;

	if (argc != 2)
		return (print_usage());
	if (open_fd(argv[1], &fd) == -1)
		return (1);
	head = input(fd, &head);
	if (close_fd(fd) == -1)
		return (2);
	if (!head)
		return (error(3));
/*mmakinen tests. Prints out content of struct list*/
	t_tetro	*temp = head;
	while (temp->next)
	{
		ft_putnbr(temp->shape_id);
		ft_putstr("\n");
		ft_putchar(temp->letter);
		ft_putchar('\n');
		temp = temp->next;
	}
	ft_putnbr(temp->shape_id);
	ft_putstr("\n");
	ft_putchar(temp->letter);
	ft_putchar('\n');
	if (head)
		free_list(head);
	return (0);
}
