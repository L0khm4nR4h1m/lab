#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int fd[2];
	pipe(fd);
	pid_t pid = fork();

	if (pid > 0) {
		close(0);
		close(fd[1]);
		dup(fd[0]);

		int num;
		int check = 0;
		printf("Waiting for number...\n");
		read(fd[0], &num, sizeof(num));
		wait(NULL);

		if (num == 0 | num == 1) {
			check = 1;
		}

		for (int i = 2; i <= num/2; i++) {
			if (num % i == 0) {
				check = 1;
				break;
			}
		}

		if (check == 0) {
			printf("The number %d is a prime number", num);
		}
		else {
			printf("The number %d is NOT a prime number", num);
		}
	}

	else if (pid == 0) {
		close(1);
		close(fd[0]);
		dup(fd[1]);

		int n;

		printf("Enter a number > ");
		scanf("%d", &n);

		write(fd[1], &n, sizeof(n));
		exit(EXIT_SUCCESS);
	}


	return EXIT_SUCCESS;
}

