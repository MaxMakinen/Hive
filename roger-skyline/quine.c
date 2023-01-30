#include <stdio.h>

char *s = "#include <stdio.h>%c%cchar *s = %c%s%c;%c%cint main() {%c    printf(s, 10, 10, 34, s, 34, 10, 10, 10, 10);%c    return 0;";

int main() {
    printf(s, 10, 10, 34, s, 34, 10, 10, 10, 10);
    return 0;
}