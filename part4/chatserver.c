#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main() {

	int a,socket_desc,new_socket,n;
	char str[25],str2[25];
	struct sockaddr_in server;
	struct sockaddr_in client;
	socklen_t csize=sizeof(client);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=htons(8888);
	
	if((socket_desc=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket could not be created");
		return 1;
	}
	
	if(bind(socket_desc,(struct sockaddr *)&server, sizeof(server)) < 0) {
		printf("Binding error");
		return 1;
	}
	
	puts("bind done");
	
	if(listen(socket_desc, 3)<0) {
		printf("Cannot listen");
	}
	
	if((new_socket = accept(socket_desc,(struct sockaddr *)&client, &csize)) < 0) {
		printf("Accept error");
		return 1;
	}
	else {
		printf("\n now connected to %s\n",inet_ntoa(client.sin_addr));
	}
	printf("\n");

	while (1) {
		listen(new_socket, 1);
		read(new_socket, str, sizeof(str));
		printf("client msg:%s", str);
		printf("\n server msg:");
		scanf("%[^\n]%*c", str2);
		write(new_socket, str2, sizeof(str2));
	} 
	
	close(new_socket);
	close(socket_desc);
	
	return 0;
}
