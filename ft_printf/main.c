#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <signal.h>

int	main(void)
{
	ft_printf("{%-10d}\n", 42);
	printf("{%-10d}\n", 42);

	ft_printf("{%10d}\n", -42);
	printf("{%10d}\n", -42);

	ft_printf("{%#3x}\n", 0);
	printf("{%#3x}\n", 0);

	ft_printf("{%#.4o}\n", 0);
	printf("{%#.4o}\n", 0);

	ft_printf("{%020p}\n", &strlen);
	printf("{%020p}\n", &strlen);

	ft_printf("{%030x}\n", 0xFFFF);
	printf("{%030x}\n", 0xFFFF);
}
