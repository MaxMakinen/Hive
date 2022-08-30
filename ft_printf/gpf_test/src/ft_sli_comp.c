#include <stdio.h>

int main(void)
{
    printf("Func call: \"test1 %%i\", 2147483647\n");
    ft_printf("test1 %i\n\n", 2147483647);
    printf("Func call: \"test2 %%i\", -2147483647\n");
    ft_printf("test2 %i\n\n", -2147483647);
    printf("Func call: \"test3 %%i\", 0\n");
    ft_printf("test3 %i\n\n", 0);
    printf("Func call: \"test4 %%i\", 1000\n");
    ft_printf("test4 %i\n\n", 1000);
    printf("Func call: \"test5 %%i\", -1000\n");
    ft_printf("test5 %i\n\n", -1000);

    printf("Func call: \"test6 %%o\", 0\n");
    ft_printf("test6 %o\n\n", 0);
    printf("Func call: \"test7 %%o\", 17\n");
    ft_printf("test7 %o\n\n", 17);
    printf("Func call: \"test8 %%o\", 1234\n");
    ft_printf("test8 %o\n\n", 1234);
    printf("Func call: \"test9 %%o\", -17\n");
    ft_printf("test9 %o\n\n", -17);
    printf("Func call: \"test10 %%o\", -1234\n");
    ft_printf("test10 %o\n\n", -1234);

    printf("Func call: \"test11 %%u\", 0\n");
    ft_printf("test11 %u\n\n", 0);
    printf("Func call: \"test12 %%u\", 17\n");
    ft_printf("test12 %u\n\n", 17);
    printf("Func call: \"test13 %%u\", 1234\n");
    ft_printf("test13 %u\n\n", 1234);
    printf("Func call: \"test14 %%u\", -12345\n");
    ft_printf("test14 %u\n\n", -12345);
    printf("Func call: \"test15 %%u\", -1000\n");
    ft_printf("test15 %u\n\n", -1000);
    printf("Func call: \"test16 %%u\", -17\n");
    ft_printf("test16 %u\n\n", -17);

    printf("Func call: \"test17 %%x\", 2147483647\n");
    ft_printf("test17 %x\n\n", 2147483647);
    printf("Func call: \"test18 %%x\", 8043919\n");
    ft_printf("test18 %x\n\n", 8043919);
    printf("Func call: \"test19 %%x\", -123456\n");
    ft_printf("test19 %x\n\n", -123456);
    printf("Func call: \"test20 %%x\", 0\n");
    ft_printf("test20 %x\n\n", 0);

    printf("Func call: \"test21 %%X\", 2147483647\n");
    ft_printf("test21 %X\n\n", 2147483647);
    printf("Func call: \"test22 %%X\", 8043919\n");
    ft_printf("test22 %X\n\n", 8043919);
    printf("Func call: \"test23 %%X\", -123456\n");
    ft_printf("test23 %X\n\n", -123456);
    printf("Func call: \"test24 %%X\", 0\n");
    ft_printf("test24 %X\n\n", 0);

    printf("Func call: \"test25 %%c\", 0\n");
    ft_printf("test25 %c\n\n", 0);
    printf("Func call: \"test26 %%c\", 65\n");
    ft_printf("test26 %c\n\n", 65);
    printf("Func call: \"test27 %%c\", 122\n");
    ft_printf("test27 %c\n\n", 122);
    printf("Func call: \"test28 %%c\", -122\n");
    ft_printf("test28 %c\n\n", -122);
}
