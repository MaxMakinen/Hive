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

	ft_printf("{%#.3x}\n", 1);
	printf("{%#.3x}\n", 1);

	ft_printf("{%#4.3x}\n", 1);
	printf("{%#4.3x}\n", 1);

	int test;
	test = ft_printf("{%020p}\n", &strlen);
	printf("ft_test = %d\n", test);
	test = printf("{%020p}\n", &strlen);
	printf("test = %d\n", test);

	test = ft_printf("{%030x}\n", 0xFFFF);
	printf("ft_test = %d\n", test);
	test = printf("{%030x}\n", 0xFFFF);
	printf("test = %d\n", test);

	test = ft_printf("{% 10.4d}\n", 4242);
	printf("ft_test = %d\n", test);
	test = printf("{% 10.4d}\n", 4242);
	printf("test = %d\n", test);

	test = ft_printf("{% u}\n", 4294967295);
	printf("ft_test = %d\n", test);
	test = printf("{% u}\n", 4294967295);
	printf("test = %d\n", test);

	test = ft_printf("%5%");
	printf("\nft_test = %d\n", test);
	test = printf("%5%");
	printf("\ntest = %d\n", test);

	test = ft_printf("%jx", 424242);
	printf("\nft_test = %d\n", test);
	test = printf("%jx", 424242);
	printf("\ntest = %d\n", test);

	test = ft_printf("%05%");
	printf("\nft_test = %d\n", test);
	test = printf("%05%");
	printf("\ntest = %d\n", test);

	test = ft_printf("% hZ%");
	printf("\nft_test = %d\n", test);
	test = printf("% hZ%");
	printf("\ntest = %d\n", test);

	test = ft_printf("%llx", 42424242);
	printf("\nft_test = %d\n", test);
	test = printf("%llx", 42424242);
	printf("\ntest = %d\n", test);
}
