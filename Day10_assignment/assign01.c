/*The child process send two numbers to the parent process via message queue. The parent process calculate the sum and return via same message queue.
The child process print the result and exit. The parent process wait for completion of the child and then exit.*/


#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MQ_KEY		0x1234

typedef struct msg {
	long type;
	int num1;
	int num2;
	int sum;
} msg_t;

int main() {
	int mqid, ret, s;
	// create message queue
	mqid = msgget(MQ_KEY, IPC_CREAT | 0600);

	if(mqid < 0) 
	{
		perror("msgget() failed");
		_exit(1);
	}

	ret = fork();
	if(ret == 0)
	{
		// child: initialize and send the message
		msg_t m1;
		m1.type = 1;
		printf("sender: enter two numbers: ");
		scanf("%d%d", &m1.num1,&m1.num2);

		ret = msgsnd(mqid, &m1, (sizeof(m1.num1)+sizeof(m1.num2)), 0);
		printf("sender: message sent: %d\n", ret);
	//	sleep(1);
		ret = msgrcv(mqid, &m1, sizeof(m1.num1),1,0);
		printf("sender: message recieved: %d\n", m1.num1);
	}
	else {
		// parent: receive the mrssage and print it
		msg_t m2;
		printf("receiver: waiting for the message...\n");
		ret = msgrcv(mqid, &m2, (sizeof(m2.num1)+sizeof(m2.num2)),1,0);
		printf("receiver: message received: %d -- %d %d\n", ret, m2.num1,m2.num2);
		m2.num1  = (m2.num1+m2.num2);
	//	m2.sum = (m2.num1+m2.num2);
		ret = msgsnd(mqid, &m2, sizeof(m2.num1), 0);
		printf("Receiver: Message sent: %d\n", ret);
		// wait for child and clean it up
		wait(&s);

		// destroy the message queue
		msgctl(mqid, IPC_RMID, NULL);
	}
	return 0;
}


