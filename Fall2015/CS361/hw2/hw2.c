#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

#define STDIN_FD 0
#define STDOUT_FD 1

#define ADDON 1
#define OVRWRITE 2
#define INFROM 3
#define NONE 0

#define NO 0
#define YES 1

// Global Vars
pid_t cpid, epid, pid;

void handlerSIGINT(int sig);
void handlerSIGTSTP(int sig);

void handlerSIGINT(int sig){
	signal(SIGINT, handlerSIGINT);
	printf(" Recieved SIGINT\n");
	if(cpid != 0){
		kill(cpid, sig);
	}
}

void handlerSIGTSTP(int sig){
	signal(SIGTSTP, handlerSIGTSTP);
	printf(" Recieved SIGTSTP\n");
	if(cpid != 0){
		kill(cpid, sig);
	}
}

int redirectCheck(char** inCommand, int* count){
	int i, j;
	for(i = 0; i < (*count); i++){
		j = 0;
		while(inCommand[i][j] != '\0'){
			if(inCommand[i][j] == '>'){
				if(inCommand[i][j + 1] == '>'){
					return ADDON;
				} else {
					return OVRWRITE;
				}
			} else if(inCommand[i][j] == '<'){
				return INFROM;
			}
			j++;
		}
	}
	return NONE;
}

char** splitter(char* strToSplit, int* count, int* flag){
	int i = 0;
	int location[256];
	// Setting up the argument count and making more clear the seperation of arguments
	location[0] = 0;
	while(strToSplit[i] != '\0'){
		if(strToSplit[i] == ' '){
			strToSplit[i]  = '\0';
			location[(*count)] = (i + 1);
			(*count)++;
			(*flag) = YES;
		} else if (strToSplit[i] == '\n' || strToSplit[i] == '\t'){
			strToSplit[i]  = '\0';
			(*flag) = YES;
		}
		i++;
	}
	// Building of the outArray
	char** outArray = malloc(sizeof(char*) * ((*count) + 1));
	outArray[(*count) + 1] = "\0";
	// Going through the input string and splitting into an array
	fflush(stdout);
	for (i = 0; i < (*count); ++i){
		outArray[i] = &strToSplit[location[i]];
	}
	return outArray;
}
char** commandShrink(char** inCommand, int count){
	char** outCommand = malloc(sizeof(char*) * (count + 1));
	outCommand[count + 1] = "\0";
	for(int i = 0; i < count; i++){
		outCommand[i] = inCommand[i];
	}
	return outCommand;
}

int main (int argv, char** argc){
	// var section
	char** command;
	char inputString[513];
	int count = 1;
	int redirect = 0;
	int file = 0;
	int flag = NO;
	int status, i, oldSTD;
	// start of program
	signal(SIGINT, handlerSIGINT);
	signal(SIGTSTP, handlerSIGTSTP);
	printf("mpeter39's shell\n$$ ");
	fgets(inputString, 513, stdin);
	command = splitter(inputString, &count, &flag);
	redirect = redirectCheck(command, &count);
	while(strncmp(inputString, "exit", 4) != 0){
		if(flag == YES){
			if(redirect == OVRWRITE){
				oldSTD = dup(1);
				for(i = 0; i <= count; i++){
					if(command[i][0] == '>'){
						if(command[i + 1] != '\0'){
							file = open(command[i + 1], O_WRONLY | O_CREAT, 0666);
						}
						command = commandShrink(command, count - 2);
						break;
					}
				}
			} else if (redirect == ADDON){
				oldSTD = dup(1);
				for(i = 0; i <= count; i++){
					if(strncmp(command[i], ">>", 2) == 0){
						if(command[i + 1] != '\0'){
							file = open(command[i + 1], O_CREAT | O_RDWR | O_APPEND, 0666);
						}
						command = commandShrink(command, count - 2);
						break;
					}
				}
			} else if (redirect == INFROM){
				oldSTD = dup(1);
				for(i = 0; i <= count; i++){
					if(command[i][0] == '<'){
						if(command[i + 1] != '\0'){
							file = open(command[i + 1], O_RDONLY);
						}
						command = commandShrink(command, count - 2);
						break;
					}
				}
			}
			//check for proper forking
			if((cpid = fork()) < 0){
				printf("***ERROR IN CHILD FORK CREATION***\n");
				exit(EXIT_FAILURE);
			} else if (cpid == 0){
				printf("Child process PID: %u\n", getpid());	
				if(redirect == OVRWRITE || redirect == ADDON){
					dup2(file, STDOUT_FD);
					close(file);
				} else if(redirect == INFROM){
					dup2(file, STDIN_FD);
					close(file);
				}	
				if(execvp(command[0], &command[0]) < 0){
					printf("Child exited because command was not handled properly\n");
					exit(EXIT_FAILURE);
				}
				exit(EXIT_SUCCESS);
			} else {
				while((epid = waitpid(cpid, &status, WNOHANG|WUNTRACED)) == 0){

				}
				if(redirect == OVRWRITE || redirect == ADDON){
					dup2(oldSTD, STDOUT_FD);
				} else if(redirect == INFROM){
					dup2(oldSTD, STDIN_FD);
				}
				if(epid == -1){
					printf("waitpid error");
					exit(EXIT_FAILURE);
				} else if(epid == cpid){
					if(WIFEXITED(status)){
						printf("Normal Exit\n");
					} else if(WIFSIGNALED(status)){
						printf("Exit from uncaught signal\n");
					} else if(WIFSTOPPED(status)){
						printf("Child process was stopped\n");
					}
				}
			}
		}
		printf("$$ ");
		fgets(inputString, 513, stdin);
		count = 1;
		flag = NO;
		command = splitter(inputString, &count, &flag);
		redirect = redirectCheck(command, &count);
	}
	// clean up
	printf("Shell Closed.\n");
	// end of program
	return 0;
}
