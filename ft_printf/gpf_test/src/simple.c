#include <stdio.h>

int main(void)
{
    char *str = "test1";
    int a = 10, b = -10, c = 0;

    printf("Func call: \"text %%d\", 10\n");
    printf("text %d\n\n", a);
    printf("Func call: \"text %%d\", -10\n");
    printf("text %d\n\n", b);
    printf("Func call: \"text %%d\", 0\n");
    printf("text %d\n\n", c);

    printf("Func call: \"text %%s after\", \"test1\"\n");
    printf("text %s after\n\n", str);
    printf("Func call: \"random %%s\", \"another\\ttest\"\n");
    printf("random %s\n\n", "another\ttest");

    printf("Func call: \"text %%p\", &a\n");
    printf("text %p\n\n", &a);

    printf("Func call: \"%%%% test %%%%\"\n");
    printf("%% test %%\n\n");
}
