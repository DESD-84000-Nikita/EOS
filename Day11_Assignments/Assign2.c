#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
		int ret,num1,num2,n1,n2,s,r;
		int arr1[2];
		int arr2[2];
		
		ret=pipe(arr1);
		ret=pipe(arr2);

		if(ret < 0){
			perror("pipe() is failed");
			_exit(1);
		}
		ret=fork();
		if(ret == 0){
			//child write process
			close(arr1[0]);
			close(arr2[1]);

			printf("Enter the two numbers:");
			scanf("%d%d",&num1,&num2);

			ret=write(arr1[1],&num1,sizeof(num1));
			ret=write(arr1[1],&num2,sizeof(num2));
//			printf("child:send the two number:%d %d\n",ret);

			ret=read(arr2[0],&r,sizeof(r));
			printf("result:%d\n",r);

			close(arr2[0]);
			close(arr1[1]);

		}
		else{
		//Parent..
			close(arr1[1]);
			close(arr2[0]);
			
			printf("Parent is waiting for data..\n");
			ret=read(arr1[0],&n1,sizeof(n1));
			ret=read(arr1[0],&n2,sizeof(n2));
//			printf("Parent pull the data from pipe: %d %d\n",ret);
			
			
			r= n1+n2;

			ret=write(arr2[1],&r,sizeof(r));


			close(arr2[1]);
			close(arr1[0]);
			waitpid(-1,&s,0);
		}

return 0;
}
