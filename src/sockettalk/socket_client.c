/* * =====================================================================================
 *
 *       Filename:  socket_client.c
 *
 *    Description:  Chat Client
 *
 *        Version:  1.0
 *        Created:  10/30/2017 12:48:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Doto (), mvd369@gmail.com
 *   Organization:  
 *                  I Pledge My Honor That I Have Abided By The Stevens Honor System
 *
 * =====================================================================================
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* promptUsername(){
	int nameSize = 8;
	char* name = (char*) malloc(nameSize*sizeof(char));
	printf("Username] ");
	fflush(stdout);
	strcpy(name,"/nick ");
	for(int nameInd=6; read(0,&name[nameInd],1); nameInd++){
		if(nameInd==nameSize){
			nameSize*=2;
			name = (char*) realloc(name,nameSize*sizeof(char));
		}
		if(name[nameInd]=='\n'){
			name[nameInd]='\0';
			break;
		}
	}
	return name;
}

static int servFD;

struct addrinfo* establishConnection(char* nick, char* host, char* port){
	int status;
	struct addrinfo hints;
	struct addrinfo *result, *servinfo;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;
	if ((status = getaddrinfo(host, port, &hints, &result)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}
	for (servinfo = result; servinfo != NULL; servinfo = servinfo->ai_next) {
		servFD = socket(servinfo->ai_family, servinfo->ai_socktype,
				servinfo->ai_protocol);
		if (servFD == -1)
			continue;
		if (connect(servFD, servinfo->ai_addr, servinfo->ai_addrlen) != -1)
			break;                  /* Success */
		close(servFD);
	}
	if (servinfo == NULL) {               /* No address succeeded */
		fprintf(stderr, "Could not connect\n");
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(result);           /* No longer needed */
	sendto(servFD,nick,strlen(nick)+1,0,servinfo->ai_addr,sizeof (servinfo->ai_addr));
	return servinfo;
}

void readingLoop(struct addrinfo* servinfo){
	fd_set rfds;
	while(1){
		FD_SET(servFD,&rfds);
		FD_SET(0,&rfds);
		select(servFD+1,&rfds,NULL,NULL,NULL);
		if(FD_ISSET(servFD,&rfds)){
			char buf;
			uint fromlen = sizeof servinfo->ai_addr;
			while(recvfrom(servFD,&buf,1,0,servinfo->ai_addr,&fromlen)){
				write(1,&buf,1);
			}
		}
		if(FD_ISSET(0,&rfds)){
			int msgSize = 8;
			char* msg = (char*) malloc(msgSize*sizeof(char));
			for(int msgInd=0; read(0,&msg[msgInd],1); msgInd++){
				if(msgInd==msgSize){
					msgSize*=2;
					msg = (char*) realloc(msg,msgSize*sizeof(char));
				}
				if(msg[msgInd]=='\n'){
					msg[msgInd]='\0';
					break;
				}
			}
		}
	}
}

int main(int argc, char *argv[]){
	printf("Started\n");
	if(argc!=3){
		printf("Usage: %s [host] [port]",argv[0]);
		exit(1);
	}
	printf("Prompt\n");
	char* nick = promptUsername();
	printf(nick);
	printf("Prompted\n");
	struct addrinfo* servinfo = establishConnection(nick,argv[1],argv[2]);
	printf("Connected\n");
	readingLoop(servinfo);
}
