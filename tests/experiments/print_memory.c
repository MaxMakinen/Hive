/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:52:27 by mmakinen          #+#    #+#             */
/*   Updated: 2022/06/18 14:51:08 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	print_hex(int num)
{
	int	hex = 0;

	hex = (num & 0xf0) >> 4;
	if (hex > 9)
		hex += 'A' - 10;
	else
		hex += '0';
	write(1, &hex, 1);
	hex = num & 0xf;
	if (hex > 9)
		hex += 'A' - 10;
	else
		hex += '0';
	write(1, &hex, 1);
}

void	print_chr(char c)
{
	if (c >= 32 && c <= 126)
		write(1, &c, 1);
	else
		write(1, ".", 1);
}

void	print_memory(const void *addr, size_t size)
{
	char	*ptr = (char *)addr;
	size_t		pos = 0;
	size_t		row = 0;
	size_t		temp = 0;

	while (pos < size)
	{
		row = 0;
		temp = pos;
		while (row < 16)
		{
			if (pos < size)
				print_hex(ptr[pos]);
			else
				write(1, "  ", 2);
			if (row % 2)
				write(1, " ", 1);
			row++;
			pos++;
		}
		pos = temp;
		row = 0;
		while (row < 16 && pos < size)
		{
			print_chr(ptr[pos]);
			row++;
			pos++;
		}
		write(1, "\n", 1);
	}
}

int	main(void)
{
	int	tab[10] = {0, 23, 150, 255,
	              12, 16, 121, 42};

	print_memory(tab, sizeof(tab));

	unsigned char	ctab[10] = {0, 23, 150, 255,
	              12, 16, 121, 42};

	write(1, "\n", 1);
	print_memory(ctab, sizeof(ctab));

	unsigned char	cttab[11] = {0, 23, 150, 255,
	              12, 16, 121, 42};

	write(1, "\n", 1);
	print_memory(cttab, sizeof(cttab));

	unsigned char	cbtab[13] = {30, 31, 32, 33,
	              125, 126, 127, 128};

	write(1, "\n", 1);
	print_memory(cbtab, sizeof(cbtab));

	int	btab[13] = {30, 31, 32, 33,
	              125, 126, 127, 128};

	write(1, "\n", 1);
	print_memory(btab, sizeof(btab));
	return (0);
}
