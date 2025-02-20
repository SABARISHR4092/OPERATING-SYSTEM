#include<stdio.h>
#include<unistd.h>
int main()
{
	printf("ProcessID:%d\n",getpid());
	printf("Parent ProcessID: %d\n",getpid());
	return 0;
}