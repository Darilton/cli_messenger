#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "../utils/utils.h"

void die_with_error(int count, ...);

int main(int argc, char *argv[]){
	char message[MESSAGE_LEN];

	if(argc != 3)
		die_with_error(4,argv[0], ": usage: ", argv[0], " <server ip> <port>\n");

	char * server_ip = argv[1];
	short port = atoi(argv[2]);

	SOCKET my_socket = socket(ADDRESS_TYPE, SOCK_STREAM, IPPROTO_TCP);
	if(my_socket < 0)
		die_with_error(3, argv[0], ": Error creating socket: ", strerror(errno));

	printf("Socket: %d\n", my_socket);
	struct sockaddr_in server;
	server.sin_port = htons(port);
	server.sin_family = ADDRESS_TYPE;
	if(!inet_pton(ADDRESS_TYPE, server_ip, &server.sin_addr.s_addr))
		die_with_error(1, "Invalid ip address: must be in form ddd.ddd.ddd.ddd\n");

	if(connect(my_socket, (struct sockaddr *) &server, sizeof(server)))
		die_with_error(2, argv[0], ": unable to connect to server\n");

	printf("Type in your messages to be sent to the echo server\n");
	while(1){
		printf("you: ");
		void * success = fgets(message, MESSAGE_LEN - 1, stdin);
		if(!success)
			break;
		send(my_socket, message, MESSAGE_LEN, 0);	
		memset(message, '\0', MESSAGE_LEN);
		recv(my_socket, message, MESSAGE_LEN, 0);	
		printf("server: %s", message);
	}
	close();
	printf("\nProgram terminated successfuly\n");
	return 0;
}