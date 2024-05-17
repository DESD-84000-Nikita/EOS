#include <stdio.h>
#include <unistd.h>
#include <signal.h>

 int  arr[2];
void sigint_handler(int sig)
{
	printf("SIGINT caught: %d\n", sig);
	close(arr[1]);
	close(arr[0]);
	_exit(0);
}

int main()
{
	char ch='A';
	int ret ;
	struct sigaction sa;
	ret=pipe(arr);
	ret=sigaction(SIGINT,&sa,NULL);
	int count=0;

	while(1)
	{
		ret=write(arr[1],&ch,1);
		count++;
		printf("bytes written:%d\n",count);
	}
return 0;
}


	
