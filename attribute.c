#include <stdio.h>
#include <stdlib.h>

struct p
{
   int a;
   char b;
   char c;
}__attribute__((aligned(4))) pp;

struct q 
{
   int a;
   char b;
   struct p n;
   char c;
}__attribute__((aligned(8))) qq;

struct p1
{
   int a;
   char b;
   char c;
}__attribute__((packed)) pp1;

struct q1
{
   int a;
   char b;
   struct p n;
   char c;
}__attribute__((packed)) qq1;


struct p2
{
   int a;
   char b;
   char c;
} pp2;

struct q2
{
   int a;
   char b;
   struct p n;
   char c;
} qq2;



int main()
{
   printf("sizeof(int)=%d, sizeof(short)=%d, sizeof(char)=%d\n",sizeof(int),sizeof(short),sizeof(char));
   printf("pp=%d, qq=%d \n", sizeof(pp),sizeof(qq));
   printf("pp1=%d, qq1=%d \n", sizeof(pp1), sizeof(qq1));
   printf("pp2=%d, qq2=%d \n", sizeof(pp2), sizeof(qq2));
   return 0;
}
