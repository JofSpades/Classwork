#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "dns.h"
static int debug=0, nameserver_flag=0;
struct stack{
  char data[255];
  struct stack *next;
};
struct stack *hist = NULL;
FILE *root;
char currentRoot[255], looking[255], orig[255];
void push(struct stack **top, char data[255]){
  int i;
  for(i = 0; i < 255; i++){
    if(data[i] == '\n'){
      data[i] = '\0';
      break;
    }
  }
  if((*top) == NULL){
    (*top) = malloc(sizeof(struct stack));
    (*top)->next = NULL;
    strcpy((*top)->data, data);
  } else {
    struct stack *temp = malloc(sizeof(struct stack));
    temp->next = (*top);
    strcpy(temp->data, data);
    (*top) = temp;
  }
}
char* pop(struct stack **top){
  if((*top) == NULL){
    return (char*)0;
  } else {
    char* retval = malloc(sizeof(char)*255);
    struct stack *temp = (*top);
    (*top) = (*top)->next;
    strcpy(retval, temp->data);
    free(temp);
    return retval;
  }
}
void print(struct stack *top){
  struct stack *iter = top;
  while(iter != NULL){
    printf("%s\n", iter->data);
    iter = iter->next;
  }
}
int isInStack(struct stack *top, char* data){
  struct stack *iter = top;
  while(iter != NULL){
    if(strcmp(iter->data, data) == 0){
      return 1;
    }
    iter = iter->next;
  }
  return 0;
}
void usage() {
	printf("Usage: hw5 [-d] -n nameserver -i domain/ip_address\n\t-d: debug\n");
	exit(1);
}
/* constructs a DNS query message for the provided hostname */
int construct_query(uint8_t* query, int max_query, char* hostname) {
	memset(query,0,max_query);
	in_addr_t rev_addr=inet_addr(hostname);
	if(rev_addr!=INADDR_NONE) {
		static char reverse_name[255];		
		sprintf(reverse_name,"%d.%d.%d.%d.in-addr.arpa",
						(rev_addr&0xff000000)>>24,
						(rev_addr&0xff0000)>>16,
						(rev_addr&0xff00)>>8,
						(rev_addr&0xff));
		hostname=reverse_name;
	}
	// first part of the query is a fixed size header
	struct dns_hdr *hdr = (struct dns_hdr*)query;
	// generate a random 16-bit number for session
	uint16_t query_id = (uint16_t) (random() & 0xffff);
	hdr->id = htons(query_id);
	// set header flags to request recursive query
	hdr->flags = htons(0x0100);	
	// 1 question, no answers or other records
	hdr->q_count=htons(1);
	// add the name
	int query_len = sizeof(struct dns_hdr); 
	int name_len=to_dns_style(hostname,query+query_len);
	query_len += name_len;
	// now the query type: A or PTR.
	uint16_t *type = (uint16_t*)(query+query_len);
	if(rev_addr!=INADDR_NONE)
		*type = htons(12);
	else
		*type = htons(1);
	query_len+=2;
	// finally the class: INET
	uint16_t *class = (uint16_t*)(query+query_len);
	*class = htons(1);
	query_len += 2;
	return query_len;
}
void getRoot(){
  char temp[255];
  if(fgets(temp, 255, root) == NULL){
    rewind(root);
    if(fgets(temp, 16, root) == NULL){
      printf("error in reading file\n");
      exit(1);
    }
  }
  int i;
  for(i = 0; i < 16; i++){
    if(temp[i] == '\n'){
      temp[i] = '\0';
    }
  }
  strcpy(currentRoot, temp);
}
int search(char hostname[255], char nameserver[255]){
  if(debug)printf("Resolving %s with server %s\n", hostname, nameserver);
  struct stack *name = NULL, *ip = NULL, *cname = NULL;
  // using a constant name server address for now.
	in_addr_t nameserver_addr=inet_addr(nameserver);
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0) {
		perror("Creating socket failed: ");
		exit(1);
	}
  struct timeval timeout;      
  timeout.tv_sec = 2;
  timeout.tv_usec = 0;
  if (setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0){
    perror("setsockopt failed");
    exit(1);
  }
	// construct the query message
	uint8_t query[1500];
	int query_len=construct_query(query,1500,hostname);
	struct sockaddr_in addr; 	// internet socket address data structure
	addr.sin_family = AF_INET;
	addr.sin_port = htons(53); // port 53 for DNS
	addr.sin_addr.s_addr = nameserver_addr; // destination address (any local for now)
	int send_count = sendto(sock, query, query_len, 0, (struct sockaddr*)&addr,sizeof(addr));
	if(send_count<0) { perror("Send failed");	exit(1); }	
	// await the response 
	uint8_t answerbuf[1500];
	int rec_count = recv(sock,answerbuf,1500,0);
  if(rec_count == -1){
	  shutdown(sock,SHUT_RDWR);
	  close(sock);
    if(errno == EAGAIN){
      printf("got timeout\n");
      push(&hist, nameserver);
      if(strcmp(nameserver, currentRoot) == 0){
        getRoot();
        return search(hostname, currentRoot);
      } else {
        return 0;
      }
    }
  }
	// parse the response to get our answer
	struct dns_hdr *ans_hdr=(struct dns_hdr*)answerbuf;
	uint8_t *answer_ptr = answerbuf + sizeof(struct dns_hdr);
	// now answer_ptr points at the first question. 
	int question_count = ntohs(ans_hdr->q_count);
	int answer_count = ntohs(ans_hdr->a_count);
	int auth_count = ntohs(ans_hdr->auth_count);
	int other_count = ntohs(ans_hdr->other_count);
	// skip past all questions
	int q;
	for(q=0;q<question_count;q++) {
		char string_name[255];
		memset(string_name,0,255);
		int size=from_dns_style(answerbuf,answer_ptr,string_name);
		answer_ptr+=size;
		answer_ptr+=4; //2 for type, 2 for class
	}
	int a;
	int got_a = 0;
  int got_ns = 0;
  int got_cn = 0;
  int got_pt = 0;
	// now answer_ptr points at the first answer. loop through
	// all answers in all sections
	for(a=0;a<answer_count+auth_count+other_count;a++) {
		// first the name this answer is referring to 
		char string_name[255];
		int dnsnamelen=from_dns_style(answerbuf,answer_ptr,string_name);
		answer_ptr += dnsnamelen;
		// then fixed part of the RR record
		struct dns_rr* rr = (struct dns_rr*)answer_ptr;
		answer_ptr+=sizeof(struct dns_rr);
		const uint8_t RECTYPE_A=1;
		const uint8_t RECTYPE_NS=2;
		const uint8_t RECTYPE_CNAME=5;
		const uint8_t RECTYPE_SOA=6;
		const uint8_t RECTYPE_PTR=12;
		const uint8_t RECTYPE_AAAA=28;
		if(htons(rr->type)==RECTYPE_A) {
			char ipaddr[255];
      strcpy(ipaddr, inet_ntoa(*((struct in_addr *)answer_ptr))); 
			if(strcmp(string_name, looking) == 0){
        printf("The name %s resolves to IP addr: %s\n", string_name, ipaddr);
        int i;
        int flag = 0;
        for(i = 0; i<255; i++){
          if((((int)orig[i]) >= 65 && ((int)orig[i]) <= 90) || (((int)orig[i]) >= 97 && ((int)orig[i]) <= 122)){
            flag = 1;
            break;
          }
        }
        if(!flag){
          printf("%s resolves to %s\n", orig, string_name);
        }
        return 1;
      } else if(strcmp(hostname, string_name) == 0){
          if(debug)printf("The name %s resolves to IP addr: %s\n\n", string_name, ipaddr);
	        shutdown(sock,SHUT_RDWR);
	        close(sock);
          return search(looking, ipaddr);
      } else if(debug){
        printf("The name %s resolves to IP addr: %s\n", string_name, ipaddr);
      }
      if(!isInStack(hist, ipaddr)){
        push(&ip, ipaddr);
      }
      got_a = 1;
		}
		// NS record
		else if(htons(rr->type)==RECTYPE_NS) {
			char ns_string[255];
			int ns_len=from_dns_style(answerbuf,answer_ptr,ns_string);
			if(debug)printf("The name %s can be resolved by NS: %s\n",string_name, ns_string);
			if(!isInStack(hist, ns_string)){
        push(&name, ns_string);
      }
      got_ns = 1;
		}
		// CNAME record
		else if(htons(rr->type)==RECTYPE_CNAME) {
			char ns_string[255];
			int ns_len=from_dns_style(answerbuf,answer_ptr,ns_string);
			if(debug)printf("The name %s is also known as %s.\n", string_name, ns_string);
			if(!isInStack(hist, ns_string)){
        push(&cname, ns_string);
      }
      got_cn = 1;
		}
		// PTR record
		else if(htons(rr->type)==RECTYPE_PTR) {
			char ns_string[255];
			int ns_len=from_dns_style(answerbuf,answer_ptr,ns_string);
			if(debug)printf("The host at %s is also known as %s.\n", string_name, ns_string);
			if(!isInStack(hist, ns_string)){
        push(&cname, ns_string);
      }
      got_pt = 1;
		}
		// SOA record
		else if(htons(rr->type)==RECTYPE_SOA) {
			if(debug)printf("Ignoring SOA record\n");
		}
		// AAAA record
		else if(htons(rr->type)==RECTYPE_AAAA)  {
			if(debug)printf("Ignoring IPv6 record\n");
		}
		else {
			if(debug)printf("got unknown record type %hu\n",htons(rr->type));
		}
		answer_ptr+=htons(rr->datalen);
	}
	shutdown(sock,SHUT_RDWR);
	close(sock);
  if(got_a){
    while(ip != NULL){
      char popped[255];
      char* retval = pop(&ip);
      strcpy(popped, retval);
      if(debug)printf("\n");
      push(&hist, popped);
      if(search(hostname, popped)){
        free(retval);
        return 1;
      }
      free(retval);
    }
  }
  if(got_cn || got_pt){
    while(cname != NULL){
      char popped[255];
      char* retval = pop(&cname);
      strcpy(popped, retval);
      strcpy(looking, retval);
      if(debug)printf("\n");
      push(&hist, popped);
      if(search(popped, currentRoot)){
        free(retval);
        return 1;
      }
      free(retval);
    }
  }
  if(got_ns){
    while(name != NULL){
      char popped[255];
      char* retval = pop(&name);
      strcpy(popped, retval);
      if(debug)printf("\n");
      push(&hist, popped);
      if(search(popped, currentRoot)){
        free(retval);
        return 1;
      }
      free(retval);
    }
  }
  return 0;
}
int main(int argc, char** argv)
{
	if(argc<2) usage();
	char hostname[255];
	char nameserver[255];
	char *optString = "-d-n:-i:";
 	int opt = getopt( argc, argv, optString );
  while( opt != -1 ) {
    switch( opt ) {      
      case 'd':
        debug = 1; 
        break;
      case 'n':
        nameserver_flag = 1; 
        strcpy(nameserver, optarg);
        break;	 		
      case 'i':
        strcpy(hostname, optarg);
        strcpy(looking, optarg);
        strcpy(orig, optarg);
        break;	
      case '?':
				usage();
      	exit(1);               
      default:
       	usage();
       	exit(1);
    }
    opt = getopt( argc, argv, optString );
  }
  if(!nameserver_flag){
    root = fopen("./root-servers.txt", "rt");
    if(root == NULL){
      printf("error in opening file\n");
      exit(1);
    }
    getRoot();
    strcpy(nameserver, currentRoot);
  }
	if(!search(hostname, nameserver)) printf("Host %s not found.\n", hostname);
	return 0;
}
