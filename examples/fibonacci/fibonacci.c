#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main (int argc, char **argv)
{
  int i, naux, n, n0, n1;
n0 = 0;
n1 = 1;
naux = 0;
i = 0;
scanf("%d", &n);
n = n - 1;
if (n == 0)
{
printf("%d", n);
}
else
{
while (i < n)
{
naux = n1;
n1 = n0 + n1;
n0 = naux;
i = i + 1;
}
printf("%d", n1);
}
exit(EXIT_SUCCESS)
}
