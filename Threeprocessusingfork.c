#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
int i;


pid_t child1, child2, child3;
if (fork() == child1)
	printf("This is child1\n");
else if (fork() == child2)
	printf("This is child2\n");
else
	printf("This is child3\n");
}

