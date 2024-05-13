/*From a parent process (A) create a child process (B). The child (B) in turn creates new child process (C) and it (C) in turn create new child (D). All these
processes should run concurrently for 5 seconds and cleaned up properly upon termination*/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int ret1,ret2,ret3,ret4,s1,s2,s3,s4;
	ret1=fork();
	if(ret1==0)
	{
		ret2=fork();
		if(ret2==0)
		{
			ret3=fork();
			if(ret3==0)
			{
				ret4=fork();
				if(ret4==0)
				{
					printf("Child %d PID: %d\n", ret4, getpid());
					printf("Child PPID: %d\n",  getppid());
					sleep(1);
					_exit(0);
				}
				printf("Child %d PID: %d\n", ret3, getpid());
                printf("Child  PPID: %d\n", getppid());
				sleep(1);
				waitpid(ret4,&s4,0);
				_exit(0);

			}
			printf("Child %d PID: %d\n", ret2, getpid());
            printf("Child PPID: %d\n",  getppid());
			sleep(1);
			waitpid(ret3,&s3,0);
			_exit(0);

		}
		printf("Child %d PID: %d\n", ret1, getpid());
		printf("Child PPID: %d\n", getppid());

		sleep(1);
		waitpid(ret2,&s2,0);
		_exit(0);

	}

	waitpid(ret1,&s1,0);
//	printf("child exit:%d\n",WEXITSTATUS(s));



return 0;
}
