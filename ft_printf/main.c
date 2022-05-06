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

	ft_printf("{%030x}\n", 0xFFFF);
	printf("{%030x}\n", 0xFFFF);

	ft_printf("{%.4s}\n", "42 is the answer");
	printf("{%.4s}\n", "42 is the answer");

	ft_printf("{%#.o, %#.0o}\n", 0, 0);
	printf("{%#.o, %#.0o}\n", 0, 0);

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

	test = ft_printf("%5%");
	printf("\nft_test = %d\n", test);
	test = printf("%5%");
	printf("\ntest = %d\n", test);

	test = ft_printf("%");
	printf("\nft_test = %d\n", test);
	test = printf("%");
	printf("\ntest = %d\n", test);

	ft_printf("{%.p}\n", 0);
	printf("{%.p}\n", 0);

	ft_printf("{%.x}\n", 0);
	printf("{%.x}\n", 0);

	ft_printf("{%p}\n", 0);
	printf("{%p}\n", 0);

	ft_printf("{%x}\n", 0);
	printf("{%x}\n", 0);

	ft_printf("{%-15p}\n", 0);
	printf("{%-15p}\n", 0);

	ft_printf("{%05%}\n", 0);
	printf("{%05%}\n", 0);

	ft_printf("{%08.3d}\n", 8375);
	printf("{%08.3d}\n", 8375);

	ft_printf("{%-5c}\n", 'B');
	printf("{%-5c}\n", 'B');

	ft_printf("{%f}\n", 5.0f / 2.0f);
	printf("{%f}\n", 5.0f / 2.0f);

	ft_printf("{%f}\n", 10.0f / 3.0f);
	printf("{%f}\n", 10.0f / 3.0f);

	ft_printf("{%f}\n", 1.0f / 3.85f);
	printf("{%f}\n", 1.0f / 3.85f);

	ft_printf("{%.2f}\n", 1.0f / 3.85f);
	printf("{%.2f}\n", 1.0f / 3.85f);

	test = ft_printf("{%.15f}\n", 1.0f / 3.85f);
	printf("test = %d\n", test);
	test = printf("{%.15f}\n", 1.0f / 3.85f);
	printf("test = %d\n", test);

	ft_printf("{%.f}\n", 1.0f / 3.85f);
	printf("{%.f}\n", 1.0f / 3.85f);

	ft_printf("{%.2f}\n", 1.225f);
	printf("{%.2f}\n", 1.225f);

	ft_printf("{%.2f}\n", 1.335f);
	printf("{%.2f}\n", 1.335f);

	ft_printf("{%.2f}\n", 0.1f + 0.2f);
	printf("{%.2f}\n", 0.1f + 0.2f);

	printf("ld size = %d d size = %d ull size = %d size_t = %d\n",\
		   sizeof(long double), sizeof(double), sizeof(unsigned long long), sizeof(size_t));

	ft_printf("{%f}\n", -42.0f);
	printf("{%f}\n", -42.0f);

	ft_printf("{%.10f}\n", 1.0f);
	printf("{%.10f}\n", 1.0f);

	ft_printf("{%Lf}\n", 0.1f + 0.2f);
	printf("{%Lf}\n", 0.1f + 0.2f);
}
