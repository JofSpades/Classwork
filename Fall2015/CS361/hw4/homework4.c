#include <fnmatch.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <dirent.h>

#define BACKLOG (1000)

/* char* parseRequest(char* request)
 * Args: HTTP request of the form "GET /path/to/resource HTTP/1.X" 
 *
 * Return: the resource requested "/path/to/resource"
 *         0 if the request is not a valid HTTP request 
 * 
 * Does not modify the given request string. 
 * The returned resource should be free'd by the caller function. 
 */
char* parseRequest(char* request) {
  //assume file paths are no more than 256 bytes + 1 for null. 
  char *buffer = malloc(sizeof(char)*257);
  memset(buffer, 0, 257);
  
  if(fnmatch("GET * HTTP/1.*",  request, 0)) return 0; 
  sscanf(request, "GET %s HTTP/1.", buffer);
  return buffer; 
}
int isLastForwardSlash(char *string){
	int iter = 1;
	while(string[iter] != '\0'){
		++iter;
	}
	if(string[iter - 1] == '/') {
		return 1;
	} else {
		return 0;
	}
}
void sendDirectory(int sock, char *builtDirectory){
	char sendingString[4096];
	sprintf(sendingString, "HTTP/1.1 200 OK \r\n");
	sprintf(sendingString, "%sServer: Mpeter39's Homework4\r\n", sendingString);
	sprintf(sendingString, "%sContent-length: %ld\r\n", sendingString, strlen(builtDirectory));
	sprintf(sendingString, "%sContent-type: text/html\r\n", sendingString);
	sprintf(sendingString, "%sKeep-Alive: timeout=15, max=100\r\n\r\n", sendingString);
	send(sock, sendingString, strlen(sendingString), 0);
	send(sock, builtDirectory, strlen(builtDirectory), 0);
}
void sendError(int sock, char *request){
	char body[4096], sendingString[4096];
	sprintf(body, "<html><title>404 Error</title>");
	sprintf(body, "%s<h1>404 Error</h1>", body);
	sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
	sprintf(body, "%s%s: %s \r\n", body, "404", "FILE NOT FOUND");
	sprintf(body, "%s<p><img src=\"404err.jpg\" alt=\"404err\" style=\"width:414px;heigth:736px\"></p>", body);
	sprintf(body, "%s<p>%s: %s</p>\r\n", body, "Winter may be coming but this file wont because it's not here</p>Requested file", request);
	sprintf(body, "%s<hr><em>Mpeter39's Homework 4 Server</em>\r\n", body);
	
	sprintf(sendingString, "HTTP/1.1 %s %s\r\n", "404", "FILE NOT FOUND");
	sprintf(sendingString, "%sContent-type: text/html\r\n", sendingString);
	sprintf(sendingString, "%sContent-length: %d\r\n", sendingString, (int)strlen(body));
	sprintf(sendingString, "%sKeep-Alive: timeout=15, max=100\r\n\r\n", sendingString);
	send(sock, sendingString, strnlen(sendingString, ((size_t)4096)), 0);
	send(sock, body, strnlen(body, ((size_t)4096)), 0);
}
void sendFile(char* filename, int sock, long int size){
	int sendingFileDescriptor, readBytes;
	char sendingString[4096], *filetype, sendingFile[size];
	if (strstr(filename, ".html")){
		filetype = "text/html";
	} else if (strstr(filename, ".jpeg")){
		filetype = "image/jpeg";
	} else if (strstr(filename, ".jpg")){
		filetype = "image/jpeg";
	} else if (strstr(filename, ".gif")){
		filetype = "image/gif";
	} else if (strstr(filename, ".pdf")){
		filetype = "application/pdf";
	} else {
		filetype = "txt/plain";
	}
	sprintf(sendingString, "HTTP/1.1 200 OK \r\n");
	sprintf(sendingString, "%sServer: Mpeter39's Homework4\r\n", sendingString);
	sprintf(sendingString, "%sContent-length: %ld\r\n", sendingString, size);
	sprintf(sendingString, "%sContent-type: %s\r\n", sendingString, filetype);
	sprintf(sendingString, "%sKeep-Alive: timeout=15, max=100\r\n\r\n", sendingString);
	send(sock, sendingString, strnlen(sendingString, ((size_t)4096)), 0);
	sendingFileDescriptor = open(filename, O_RDONLY, 0);
	while(1) {
		readBytes = read(sendingFileDescriptor, sendingFile, size);
		if(readBytes == 0){
			break;
		}
		send(sock, sendingFile, readBytes, 0);
	} 
	close(sendingFileDescriptor);
}
/* Your program should take two arguments:
 * 1) The port number on which to bind and listen for connections, and
 * 2) The directory out of which to serve files.
 */
int main(int argc, char** argv) {
    /* For checking return values. */
    int retval;
    if(argc != 3){
      perror("USAGE: ./homework4 <port> <directory>");
      exit(1);
    }
    retval = chdir(argv[2]);
     if (retval < 0){
       perror("Error setting root directory");
       exit(1);
    }
    /* Read the port number from the first command line argument. */
    int port = atoi(argv[1]);

    /* Create a socket to which clients will connect. */
    int server_sock = socket(AF_INET6, SOCK_STREAM, 0);
    if(server_sock < 0) {
        perror("Creating socket failed");
        exit(1);
    }


    /* A server socket is bound to a port, which it will listen on for incoming
     * connections.  By default, when a bound socket is closed, the OS waits a
     * couple of minutes before allowing the port to be re-used.  This is
     * inconvenient when you're developing an application, since it means that
     * you have to wait a minute or two after you run to try things again, so
     * we can disable the wait time by setting a socket option called
     * SO_REUSEADDR, which tells the OS that we want to be able to immediately
     * re-bind to that same port. See the socket(7) man page ("man 7 socket")
     * and setsockopt(2) pages for more details about socket options. */
    int reuse_true = 1;
    retval = setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &reuse_true,
                        sizeof(reuse_true));
    if (retval < 0) {
        perror("Setting socket option failed");
        exit(1);
    }

    /* Create an address structure.  This is very similar to what we saw on the
     * client side, only this time, we're not telling the OS where to connect,
     * we're telling it to bind to a particular address and port to receive
     * incoming connections.  Like the client side, we must use htons() to put
     * the port number in network byte order.  When specifying the IP address,
     * we use a special constant, INADDR_ANY, which tells the OS to bind to all
     * of the system's addresses.  If your machine has multiple network
     * interfaces, and you only wanted to accept connections from one of them,
     * you could supply the address of the interface you wanted to use here. */
    
   
    struct sockaddr_in6 addr;   // internet socket address data structure
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(port); // byte order is significant
    addr.sin6_addr = in6addr_any; // listen to all interfaces

    
    /* As its name implies, this system call asks the OS to bind the socket to
     * address and port specified above. */
    retval = bind(server_sock, (struct sockaddr*)&addr, sizeof(addr));
    if(retval < 0) {
        perror("Error binding to port");
        exit(1);
    }

    /* Now that we've bound to an address and port, we tell the OS that we're
     * ready to start listening for client connections.  This effectively
     * activates the server socket.  BACKLOG (#defined above) tells the OS how
     * much space to reserve for incoming connections that have not yet been
     * accepted. */
    retval = listen(server_sock, BACKLOG);
    if(retval < 0) {
        perror("Error listening for connections");
        exit(1);
    }
    int sock, filePoint = 0;
    char buffer[4096], filename[4096], *request;
    struct sockaddr_in remote_addr;
    struct stat status;
    unsigned int socklen = sizeof(remote_addr);

    while(1) {
        /* Accept the first waiting connection from the server socket and
         * populate the address information.  The result (sock) is a socket
         * descriptor for the conversation with the newly connected client.  If
         * there are no pending connections in the back log, this function will
         * block indefinitely while waiting for a client connection to be made.
         * */
        sock = accept(server_sock, (struct sockaddr*) &remote_addr, &socklen);
        if(sock < 0) {
            perror("Error accepting connection");
            exit(1);
        }

        /* At this point, you have a connected socket (named sock) that you can
         * use to send() and recv(). */
	memset(buffer, 0, 4096);
	memset(filename, 0, 4096);
	filePoint = 0;
	while (1) {
		retval = recv(sock, &buffer[filePoint], sizeof(buffer), 0);
		if (retval < 0) {
			perror("Error in receving file");
			break;
		} else {
			filePoint += retval; 
			if (strstr(buffer, "\r\n\r\n")){
				break;
			}
		}
	}
	filename[0] = '.';
	request = parseRequest(buffer);
	if(request == 0){
		free(request);
		continue;
	}
	strncpy(&filename[1], request, 4095);
	//if ((strncmp(filename, "./\0", 3)) == 0){
	//	strcat(filename, "index.html");
	//}
	if (!(stat(filename, &status) < 0)){
		if (S_ISDIR(status.st_mode)) {
			//open directory given then look for a index.html otherwise 
			//send a list of files
			DIR *requestedDirectory;
			struct dirent *ent;
			char indexFile[512], fullDirectory[512];
			if ((requestedDirectory = opendir(filename)) != NULL) {
				char builtDirectory[8192];
				sprintf(builtDirectory, "<html><title>Directory for %s</title>", filename);
				sprintf(builtDirectory, "%s<h1>Directory for %s</h1>", builtDirectory, filename);
				sprintf(builtDirectory, "%s<body bgcolor=""ffffff"">\r\n", builtDirectory);
				if(isLastForwardSlash(filename)) {
					sprintf(indexFile, "%sindex.html", filename);
				} else {
					sprintf(indexFile, "%s/index.html", filename);
				}
				while ((ent = readdir (requestedDirectory)) != NULL) {
					if((strncmp(ent->d_name, "index.html\0", 11)) == 0){
						stat(indexFile, &status);
						sendFile(indexFile, sock, status.st_size);
						break;
					} else {
						if(ent->d_name[0] != '.') {
							if(isLastForwardSlash(filename)) {
								sprintf(fullDirectory, "%s%s", filename, ent->d_name);
							} else {
								sprintf(fullDirectory, "%s/%s", filename, ent->d_name);
							}
							sprintf(builtDirectory, "%s<p><a href=\"%s\">%s</a>\r\n", builtDirectory, &fullDirectory[1], ent->d_name);
						}
					}
				}
				sprintf(builtDirectory, "%s<hr><em>Mpeter39's Homework 4 Server </em>\r\n", builtDirectory);
				sendDirectory(sock, builtDirectory);
				closedir(requestedDirectory);
			} else {
				// unable to open
				sendError(sock, request);
			}
		} else if (S_ISREG(status.st_mode)) {
			//return the file requested of us
			sendFile(filename, sock, status.st_size);
		} else {
			//unsupported type
			sendError(sock, request);
		}
	} else {
		sendError(sock, request);
	}
        /* Tell the OS to clean up the resources associated with that client
         * connection, now that we're done with it. */
        close(sock);
    }
    close(server_sock);
}
