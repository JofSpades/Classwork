#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>

#ifndef FD_COPY
#define FD_COPY(f, t)   (void)(*(t) = *(f))
#endif

int main(int argc, char **argv) {	
	// turn off buffering on stdout
	setbuf(stdout, NULL);

	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	getaddrinfo(NULL, "8080", &hints, &res);

	int server_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if(server_sock < 0) {
		perror("Creating socket failed: ");
		exit(1);
	}


	int ret = bind(server_sock, res->ai_addr, res->ai_addrlen);
	if(ret < 0) {
		perror("Error binding to port");
		exit(1);
	}

	int yes=1;
	if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}

	/* workaround for funny OS X bug - need to start listening without select */
	ret=fcntl(server_sock, F_SETFL, O_NONBLOCK);
	if(ret<0) { perror("fcntl"); } 
	if (listen (server_sock, 1) < 0) { perror ("listen"); exit(1); } 
	fcntl(server_sock, F_SETFL, 0);
	
	/* data structure for tracking each client */
	struct client_state {
		struct client_state *prev;
		struct client_state *next;
		int message_count;
		int socket;
	};
	struct client_state *clients=0;
	int client_count = 0;

	/* initializing data structure for select call */
	fd_set readset;
	FD_ZERO(&readset);
	FD_SET(server_sock,&readset);	

	while(1) {
		fd_set rdyset;
		FD_COPY(&readset,&rdyset);
		int rdy = select(FD_SETSIZE,&rdyset,0,0,0);

		/* if the server_sock has a new connection coming in, accept it */
		if(FD_ISSET(server_sock,&rdyset)) {
			int sock;
			struct sockaddr_in remote_addr;
			unsigned int socklen = sizeof(remote_addr); 
			
			sock = accept(server_sock, (struct sockaddr*)&remote_addr, &socklen);
			if(res < 0) { perror("Error accepting connection"); exit(1); }

			/* allocate and initialize new client state */
			struct client_state *state=
				(struct client_state*)malloc(sizeof(struct client_state));
			state->next=clients;
			if(clients)
				clients->prev=state;
			state->prev=0;
			state->message_count=0;
			clients=state;
			state->socket=sock;
			client_count++;
			printf("Accepted connection, now %d concurrent clients\n",client_count);
			/* add new socket to fd_set for select */
			FD_SET(sock,&readset);
		}

		/* if any of the active clients are ready to deliver a message,
			 read it and print it */
		struct client_state *clstate = clients;
		while(clstate) {
			if(FD_ISSET(clstate->socket,&rdyset)) {
				char buf[255];
				memset(buf,0,255);
				int rec_count = recv(clstate->socket,buf,255,0);
				if(rec_count > 0) {
					printf("%d: %s (%d clients)\n",clstate->message_count,buf,client_count);
					clstate->message_count++;
				}
				/* if we got nothing, that means the connection is closed */
				else {
					printf("closing connection...\n");
					if(clstate->prev == 0) {
						clients = clstate->next;
						if(clients)
							clients->prev = 0;
					}
					else {
						clstate->prev->next = clstate->next;						
						if(clstate->next) 
							clstate->next->prev = clstate->prev;
					}					
					client_count--;

					printf("Client closed connection. Now %d clients.\n",client_count);
					shutdown(clstate->socket,SHUT_RDWR);
					close(clstate->socket);						
					FD_CLR(clstate->socket,&readset);
					struct client_state *tofree = clstate;
					clstate = clstate->next;
					free(tofree);					
					continue;
				}
			} // end if(FD_ISSET...
			clstate=clstate->next;
		} // end while
	}
	shutdown(server_sock,SHUT_RDWR);
}
