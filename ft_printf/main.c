#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <signal.h>

int	main(void)
{
/*
	ft_printf("{%-10d}\n", 42);
	printf("{%-10d}\n", 42);

	ft_printf("{%10d}\n", -42);
	printf("{%10d}\n", -42);

	ft_printf("{%# x}\n", 1);
	printf("{%# x}\n", 1);

	ft_printf("{% d}\n", -9999);
	printf("{% d}\n", -9999);

	ft_printf("{%.d, %.0d}\n", 0, 0);
	printf("{%.d, %.0d}\n", 0, 0);

	ft_printf("{%3.d, %3.0d}\n", 0, 0);
	printf("{%3.d, %3.0d}\n", 0, 0);

	ft_printf("{%.d, %.0d}\n", 10, 10);
	printf("{%.d, %.0d}\n", 10, 10);

	ft_printf("{% 03d}\n", 0);
	printf("{% 03d}\n", 0);

	ft_printf("{%+-3d}\n", 0);
	printf("{%+-3d}\n", 0);

	ft_printf("{%3d}\n", 0);
	printf("{%3d}\n", 0);

	ft_printf("{%d}\n", 0);
	printf("{%d}\n", 0);

	ft_printf("{%3.4d}\n", 0);
	printf("{%3.4d}\n", 0);

	ft_printf("{%3.3d}\n", 0);
	printf("{%3.3d}\n", 0);

	ft_printf("{%3.2d}\n", 0);
	printf("{%3.2d}\n", 0);

	ft_printf("{%020p}\n", &strlen);
	printf("{%020p}\n", &strlen);

	ft_printf("{%030x}\n", 0xFFFF);
	printf("{%030x}\n", 0xFFFF);

	ft_printf("{%.4s}\n", "42 is the answer");
	printf("{%.4s}\n", "42 is the answer");

	ft_printf("{%#.o, %#.0o}\n", 0, 0);
	printf("{%#.o, %#.0o} THIS IS WRONG! TRY ON OTHER OS. SEND BUGREPORT ABOUT PRINTF ABERRANT BEHAVIOUR\n", 0, 0);

	ft_printf("{%#.x, %#.0x}\n", 0, 0);
	printf("{%#.x, %#.0x}\n", 0, 0);

	ft_printf("{%#o, %#0o}\n", 0, 0);
	printf("{%#o, %#0o}\n", 0, 0);

	ft_printf("{%#x, %#0x}\n", 0, 0);
	printf("{%#x, %#0x}\n", 0, 0);

	ft_printf("{%#o, %#o}\n", 5, 10);
	printf("{%#o, %#o}\n", 5, 10);

	ft_printf("{a%ob%oc%od}\n", 0, 55555, 100000);
	printf("{a%ob%oc%od}\n", 0, 55555, 100000);

	ft_printf("{%#.3o}\n", 1);
	printf("{%#.3o}\n", 1);

	ft_printf("{%#4.3o}\n", 1);
	printf("{%#4.3o}\n", 1);
*/
	
	ft_printf("{%020p}\n", &strlen);
	printf("{%020p}\n", &strlen);

	ft_printf("{%030x}\n", 0xFFFF);
	printf("{%030x}\n", 0xFFFF);

}
