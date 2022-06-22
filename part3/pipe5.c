#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void parentTask(int fd[2]) {
	close(0);	
	close(fd[1]);
	dup(fd[0]);
	
	int num;
	int check = 0;
	read(fd[0], &num, sizeof(num));
	
	printf("Waiting for number...\n");
	wait(NULL);

  	if (num == 0 || num == 1) {
    		check = 1;
	}

  	for (int i = 2; i <= num / 2; i++) {

    		if (num % i == 0) {
      			check = 1;
      			break;
    		}
  	}

  	if (check == 0) {
    		printf("The number %d is a prime number.\n\n", num);
	}
  	else {
    		printf("The number %d is not a prime number.\n\n", num);
	}
}

void childTask(int fd[2]) {
	int n;
	printf("\nEnter a number > ");
	scanf("%d", &n);
	
	close(1);
	close(fd[0]);
	dup(fd[1]);

	write(fd[1], &n, sizeof(n));
	exit(EXIT_SUCCESS);
}

int main(void) {
	int fd[2];
	pipe(fd);
	pid_t pid = fork();

	if (pid > 0) {
		parentTask(fd);
	}
	else if (pid == 0) {
		childTask(fd);
	}

	return EXIT_SUCCESS;
}

