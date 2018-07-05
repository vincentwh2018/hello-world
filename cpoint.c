#include <stdio.h>

void fun(char *p)
{
    p[0] += 20;
    p[1] += 20;
    p[2] += 20;
    p[3] += 20;
    p = (char*)3; 
}

int main()
{
    int a = 112, b = -1;
    int *d = &a;
    int c = 0;

    char q[4] = {0, 1, 2, 3};
    char *p;
    char *m[20];

    printf("sizeof(m)=%d sizeof(q)=%d\n", sizeof(m), sizeof(q));

    c = *&a;
    printf("c=%d\n", c);


    fun(q);
    p = q;
    fun(p);
    printf("q[0]=%d, q[1]=%d, q[2]=%d, q[3]=%d\n", q[0], q[1], q[2], q[3]);

    return 0;
}

