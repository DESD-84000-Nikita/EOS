#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>


int main()
{
	int ret, s, i,j;
	i=1;
	while(1) 
	{
		ret = fork();
		if(ret == 0)
		{
			printf("Child Process\n");
			_exit(0);
		}
		else if(ret == -1) // fork() failed
			break;
		else {
				i++;
				printf("child count: %d\n", i);
			}			
		}
	for(j=1; j<=i; j++)
	wait(&s);
}
