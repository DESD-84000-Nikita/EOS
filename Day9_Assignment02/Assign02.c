#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

int main()
{
	int ret,pid,signum;


	printf("Enter pid  and signum\n");
	scanf("%d  %d",&pid,&signum);

	ret=kill(pid,signum);
	if(ret == 0)
	{
		printf("Killed!\n");
	}
	else
	{
		printf("Failed\n");
		_exit(1);
	}
return 0;
}
