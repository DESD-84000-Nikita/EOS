#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	int a[4];
	int s;

	char *file[]={"circle.c","square.c","rectangle.c","main.c"};
	// child processes compile
	for(int i =0 ;i<4;i++)
	{
		a[i]=fork();
		if (a[i] == 0)
		{
			char *cmd = "gcc";
			char *args[] = {cmd,"-c",file[i],NULL};
			execvp(cmd,args);
			exit(0);

		}

	}

	for(int i = 0; i < 4; i++)
	{
		waitpid(a[i],&s,0);
		if(WEXITSTATUS(s) != 0)
		{
			printf("fail %s\n",file[i]);
			exit(0);

		}


	}

	int d = fork();
	if (d == 0)
	{
		char *args[] = {"gcc","-o","program.out","circle.o","square.o","rectangle.o","main.o",NULL};
		execvp(args[0],args);
		exit(0);

	}

	waitpid(d,&s,0);
	if(WEXITSTATUS(s) != 0)
	{
		printf("link fail\n");
		exit(0);
	}


	int c = fork();
	if (c == 0)
	{
		execl("./program.out","program.out",NULL);
		exit(0);
	}

	waitpid(c,&s,0);
	if (WEXITSTATUS(s))
	{
		printf("status %d\n",WEXITSTATUS(s));

	}

	return 0;









}
























