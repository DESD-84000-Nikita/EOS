#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

// p1 -- writer
int main() {
	int fd, cnt;
	int num1,result;
	int num2;
	fd = open("/tmp/client_fifo", O_WRONLY);
	if(fd < 0) {
		perror("open() failed");
		_exit(1);
	}


	printf("enter a two numbers: ");
	scanf("%d %d",&num1,&num2);

	cnt = write(fd, &num1,sizeof(num1) );
	cnt = write(fd, &num2,sizeof(num2) ); 


	fd = open("/tmp/server_fifo", O_RDONLY);
	
	if(fd < 0)
	{
		perror("open() failed");
		_exit(2);
	}

	cnt=read(fd,&result,sizeof(result));
	printf("result:%d\n",result);
	close(fd);
	close(fd);
	return 0;
}

