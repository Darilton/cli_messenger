#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "../utils/utils.h"

int main(int argc, char *argv[]){
	if(argc != 2)
		die_with_error(4, argv[0], ": usage: ", argv[0], "<port>\n");
	
	short port = atoi(argv[1]);

	SOCKET my_sock = socket(ADDRESS_TYPE, SOCK_STREAM, IPPROTO_TCP);
	if(!my_sock)
		die_with_error(3, argv[0], ": Error creating socket: ", strerror(errno));

	struct sockaddr_in local_address;
	memset(&local_address, 0, sizeof(local_address));
	local_address.sin_port = htons(port);
	local_address.sin_family = ADDRESS_TYPE;
	local_address.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(my_sock, (struct sockaddr *) &local_address, sizeof(local_address)) < 0)
		die_with_error(2,argv[0], ": Could not bind to given address\n");

	if(listen(my_sock,1) < 0)
		die_with_error(2,argv[0], ": listen() failed\n");

	printf("Server listening at http://0.0.0.0:%d\n",  port);

	struct sockaddr_in clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);
	char message[MESSAGE_LEN];
	SOCKET clientSock = accept(my_sock, (struct sockaddr *) &clientAddr, &clientAddrSize);

	if(clientSock < 0)
		die_with_error(2,argv[0], ": Error while establishing connection to client\n");

	printf("Connected to client: %s\n", inet_ntoa(clientAddr.sin_addr));
	int num_bytes;
	do{
		num_bytes = recv(clientSock, message, MESSAGE_LEN - 1 , 0);
		printf("client: %s\n", message);
		send(clientSock, message, MESSAGE_LEN - 1 , 0);
	}while(num_bytes > 0);

	return 0;
}
