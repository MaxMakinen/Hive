#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
	int	test = 0;

	ft_printf("{%x}\n", 0);
	printf("{%x}\n", 0);

	ft_printf("{%-15p}\n", 0);
	printf("{%-15p}\n", 0);

	ft_printf("{%x}\n", 0);
	printf("{%x}\n", 0);

	ft_printf("{%-15p}\n", &test);
	printf("{%-15p}\n", &test);
}
