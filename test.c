#include <stdio.h>
#include <string.h>

int main()
{
    char x='x';
    printf("size of x = %lu\n", sizeof(x));
    printf("size of 'x' = %lu\n", sizeof('x')); //in C language, const char is an int
    printf("size of char 'x' = %lu\n", sizeof((char)'x'));
    printf("size of(\"\") = %lu\n", sizeof(""));
    printf("strlen of(\"\") = %lu\n", strlen(""));

    return 0;
}

