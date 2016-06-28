#include <stdlib.h>
#include <stdio.h>
int main()
{
int i, sum=0;

for (i = 0; i< 6;i++)
{
sum = sum + i;
printf("Sum after ith iteration is: %d\n", sum);
}

printf("Sum is equal to %d", sum);

return 0;
 }
