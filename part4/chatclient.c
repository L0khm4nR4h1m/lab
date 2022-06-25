#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char*argv[]) {

	int a,socket_desc;
	char str[20],str2[20];
	struct sockaddr_in server;
	
	server.sin_addr.s_addr=inet_addr("192.168.1.222");
	server.sin_family=AF_INET;
	server.sin_port=htons(8888);
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	
	if(socket_desc < 0) {
		printf("Could not create socket");
		return 1;
	}
	
	if(connect(socket_desc,(struct sockaddr*)&server, sizeof(server)) < 0) {
		printf("Connect error");
		return 1;
	}
	
	printf("\nclient connected to 192.168.1.222\n");
	printf("\n");

	while (1) {
		printf("client msg:");
		scanf("%[^\n]%*c", str);
		write(socket_desc, str, sizeof(str));
		listen(socket_desc, 1);
		read(socket_desc, str2,sizeof(str2));
		printf("server msg:%s", str2);
		printf("\n");
	} 
	
	close(socket_desc);
	return 0;
}
