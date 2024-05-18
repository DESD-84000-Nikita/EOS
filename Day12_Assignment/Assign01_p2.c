#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// p2 -- reader
int main() {
	int fd, cnt;
	int num1,num2,result;
	fd = open("/tmp/client_fifo", O_RDONLY);
	if(fd < 0) {
		perror("open() failed");
		_exit(1);
	}

	printf("waiting for data...\n");
	cnt = read(fd, &num1, sizeof(num1));
	cnt = read(fd, &num2,sizeof(num2) ); 
	
	printf("num1:%d num2:%d\n",num1,num2);
	


	fd = open("/tmp/server_fifo", O_WRONLY);
	
	result= num1+num2;
	cnt= write(fd,&result,sizeof(result));
	printf("result:%d\n",result);

	close(fd);
	close(fd);
	return 0;
}


