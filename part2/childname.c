#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void childTask() {
	char name[10] = {};
	printf("Hello, please tell me my name! > ");
	scanf("%s", name);
	printf("My name is %s", name);
	printf("\nMy PID is %d", getpid());
	printf("\n\n");
	exit(0);
}

void parentTask() {
	printf("I am parent with PID = %d", getpid());
	printf("waiting for child processes to finish...\n\n");
	wait(NULL);
	printf("Job is done\n\n");
}

int main() {
	for (int i = 0; i < 4; i++) {
		pid_t pid = fork();

		if (pid == 0) {
			childTask();
		}
		else {
			parentTask();
		}
	}
	return EXIT_SUCCESS;
}

