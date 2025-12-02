#include <stdio.h>
#include <stdlib.h>

/* Initilize a prefixed length string with the specified string in 'init' of length 'len'. */
char *ps_create(char *init, int len)
{
    char *s = malloc(1 + len + 1);
    unsigned char *lenptr = (unsigned char *)s;
    *lenptr = len;
    for (int j = 0; j < len; j++)
    {
        s[j + 1] = init[j];
    }
    s[len + 1] = 0;
    return s;
}

/* Print the prefixed length string. */
void ps_print(char *s)
{
    unsigned char *lenptr = (unsigned char *)s;
    for (int j = 0; j < *lenptr; j++)
    {
        putchar(s[j + 1]);
    }
    putchar('\n');
}

char *ps_getc(char *s)
{
    return s + 1;
}

int main(void)
{
    char *mystr = ps_create("Hello World", 11);
    ps_print(mystr);
    ps_print(mystr);
    printf("%s\n", ps_getc(mystr));
    free(mystr);
    return 0;
}
