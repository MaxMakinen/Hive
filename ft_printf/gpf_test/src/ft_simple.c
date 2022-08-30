#include <stdio.h>

int main(void)
{
    char *str = "test1";
    int a = 10, b = -10, c = 0;

    printf("Func call: \"text %%d\", 10\n");
    ft_printf("text %d\n\n", a);
    printf("Func call: \"text %%d\", -10\n");
    ft_printf("text %d\n\n", b);
    printf("Func call: \"text %%d\", 0\n");
    ft_printf("text %d\n\n", c);

    printf("Func call: \"text %%s after\", \"test1\"\n");
    ft_printf("text %s after\n\n", str);
    printf("Func call: \"random %%s\", \"another\\ttest\"\n");
    ft_printf("random %s\n\n", "another\ttest");

    printf("Func call: \"text %%p\", &a\n");
    ft_printf("text %p\n\n", &a);

    printf("Func call: \"%%%% test %%%%\"\n");
    ft_printf("%% test %%\n\n");
}
