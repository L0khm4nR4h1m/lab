#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

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
	
	printf("\nclient connected to 192.168.1.222");
	printf("\nCLIENT");
	scanf("%s", &str);
	
	if(write(socket_desc, str, sizeof(str)) < 0) {
		printf("\n Message cannot be send");
	}
	
	do {
		listen(socket_desc, 3);
		read(socket_desc, str2,sizeof(str2));
		printf("\nserver msg:%s", str2);
		printf("\nclient msg:");
		scanf("%s", &str);
		a=strcmp(str2, "BYE");
		write(socket_desc, str2, sizeof(str2));
	} 
	while(a!=0);
	
	close(socket_desc);
	return 0;
}
