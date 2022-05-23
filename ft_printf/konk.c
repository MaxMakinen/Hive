#include <stdio.h>

int ft_bit(int step);

int main(void)
{
	printf("1%32st\n", "fudge");
	printf("2%-32st\n", "fudge");
	printf("3%-+32st\n", "fudge");
	printf("4%+-32st\n", "fudge");
	printf("5%+32st\n", "fudge");
	printf("6%032st\n", "fudge");
	printf("7%10.32st\n", "fudge");
	printf("8%-10.32st\n", "fudge");
	printf("9%3.4st\n", "fudge");
	printf("10%32.st\n", "fudge");
	printf("11%.008st\n", "fudge");
	printf("12% 0+-8.06st\n", "fudge");
	printf("13% 0-+-8.06st\n", "fudge");
	printf("14% 0-+8.06st\n", "fudge");
	printf("15% -0+8.06dt\n\n", 12);
	printf("16%#0-8xt\n", 0x12);
	printf("17%-#08xt\n", 0x12);
	printf("18%+ #8xt\n", 12);
	printf("19% +#8xt\n", 12);
	printf("\n16%-8xt\n", 0x12);
	printf("17%08xt\n", 0x12);
	printf("18% 8xt\n", 12);
	printf("19%+8xt\n", 12);
	printf("19%#8o\n", 0X12);
	printf("\n20%8.03dt\n", 12);
	printf("21% -0+8.06dt\n", 0);
	printf("22% -0+8.0dt\n", 0);
	printf("bit 1 %d\n", 1);
	printf("bit 2 %d\n", 1 << 2);
	printf("ft_bit 0 %d\n", ft_bit(0));
	printf("ft_bit 1 %d\n", ft_bit(1));
	printf("ft_bit 2 %d\n", ft_bit(2));
	printf("ft_bit 3 %d\n", ft_bit(3));
	printf("ft_bit 4 %d\n", ft_bit(4));
}
