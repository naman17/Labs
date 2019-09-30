#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msg_st {
	long int my_msg_type;
	float temp;
};

int main(){

	int running = 1;
	int msgid;
	struct my_msg_st some_data;	
	long int msg_to_receive = 0;
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if(msgid == -1){
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	while(running) {
		if (msgrcv(msgid, (void *)&some_data, sizeof(float), msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error %d\n", errno);
			exit(EXIT_FAILURE);
		}

		printf("The temperature in Centigrade is %f\n", some_data.temp);
		float fara = some_data.temp*9/5 + 32;	
		printf("The temperature in Farenheit is %f\n", fara);
	}

if (msgctl(msgid, IPC_RMID, 0) == -1) {
	fprintf(stderr, "msgctl(IPC_RMID) failed\n");
	exit(EXIT_FAILURE);
}
exit(EXIT_SUCCESS);
}


