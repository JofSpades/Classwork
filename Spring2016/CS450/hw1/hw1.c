#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <libgen.h>

int main(int argc, char** argv) 
{	
    if(argc < 2 || argc > 2){
        printf("***NOT CORRECT AMOUNT OF ARGUMENTS***\nUSAGE: hw1 <request url>\n");
        exit(1);
    }
    char rawURL[8192];
    rawURL[0] = '\0';
    int sendCount = 0;
    int recvCount = 0;
    int total = 0;
    int retval = 0;
    char buf[4097];
    char requestString[8193];
    strcpy(rawURL, argv[1]);
    char* useableURLStart = strstr(rawURL, "//");
    char* useableURLend = strchr(useableURLStart + 2, '/');
    if(useableURLend == NULL){
        useableURLend = (useableURLStart + 2) + (strlen(rawURL) - 1);
    }
    char useableURL[512];
    char requestFile[512];
    char filename[512];
    useableURL[0] = '\0';
    requestFile[0] = '\0';
    filename[0] = '\0';
    requestString[0] = '\0';
    strncpy(useableURL, (useableURLStart + 2), (int)((useableURLend -2) - useableURLStart));
    printf("%s\n", useableURL);
    fflush(stdout);
    if(strcmp("\0",(useableURLend + 5)) == 0){
        strcpy(requestFile, "/"); 
        strcpy(filename, "./index.html");
    } else {
        strcpy(requestFile, useableURLend);
        sprintf(filename, ".%s", strrchr(requestFile, '/'));
    }
    printf("Request:%s\nFile:%s\n",requestFile, filename);
    fflush(stdout);
    struct addrinfo hints;
    struct addrinfo * result, * rp;
    int sock_fd, s;
    hints.ai_socktype = SOCK_STREAM;
    memset(&hints,0,sizeof(struct addrinfo));
    s = getaddrinfo(useableURL,"80",&hints,&result);
    if (0 != s){
        perror("error populating address structure");
        exit(1);
    }
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sock_fd = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
        if (sock_fd == -1){continue;}
        if (connect(sock_fd, rp->ai_addr, rp->ai_addrlen) != -1){break;}
        close(sock_fd);
    }
    if (rp == NULL) {
        fprintf(stderr, "could not connect\n");
        exit(1);
    }
    memset(&buf,0,sizeof(buf));
    sprintf(requestString, "GET %s HTTP/1.0\r\n", requestFile);
    sprintf(requestString, "%shost: %s \r\n\r\n", requestString, useableURL);
    while(sendCount < strlen(requestString)){
        retval = send(sock_fd, requestString + sendCount, strlen(requestString) - sendCount, 0);
        if(retval == -1){exit(1);}
        sendCount += retval;
    }
    while(1){
        retval = recv(sock_fd, &buf[recvCount], 8192 - recvCount, 0);
        if(retval > 0){
            recvCount += retval;
            total += retval;
        }
        if(strstr(buf, "\r\n\r\n")){
            break;
        }
    }
    //printf("%s\n%s", buf, strstr(buf, "200 OK\r\n"));
    if(strstr(buf, "200 OK\r\n") != NULL){
        char* htmlStart = (strstr(buf, "\r\n\r\n") + 4);
        FILE* file = fopen(filename, "w+");
        fwrite(htmlStart, (int)((&buf[total]) - htmlStart), 1, file);
        while((retval = recv(sock_fd, &buf, 4096, 0)) > 0){
            fwrite(&buf, retval, 1, file);
        }
        fclose(file);
    } else {
        exit(1);
    }
    freeaddrinfo(result);
    shutdown(sock_fd,SHUT_RDWR);
    return 0;
}
