#include <stdio.h>
#include <string.h>

void strrev(char *s);

int main(int nArgs, char *vArgs[])
{
    char line[] = "Hello world again!";

    printf("%s\n", line);
    strrev(line);
    printf("%s\n", line);

    return 0;
}

void strrev(char *s)
{
    int lenght = strlen(s);

    lenght -= 1;
    for (int i = 0; i <= ((lenght / 2)); i++) {
        char c = s[lenght - i];
        s[lenght - i] = s[i];
        s[i] = c;
    }
}
