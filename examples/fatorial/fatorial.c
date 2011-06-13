#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main (int argc, char **argv)
{
  int produto, n;
scanf("%d", &n);
produto = 1;
while (n > 1)
{
produto = produto * n;
n = n - 1;
}
printf("%d", produto);
exit(EXIT_SUCCESS)
}
