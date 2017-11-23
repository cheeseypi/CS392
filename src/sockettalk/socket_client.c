/*
 * =====================================================================================
 *
 *       Filename:  socket_client.c
 *
 *    Description:  Client for sockettalk
 *
 *        Version:  1.0
 *        Created:  11/15/2017 02:45:06 PM
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
#include <poll.h>
#include <signal.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int connect_serv(char* host, char* port){
	struct addrinfo hints, *servinfo;

	memset(&hints, 0, sizeof hints);
	hints.ai_family=AF_INET;
	hints.ai_socktype=SOCK_STREAM;

	if(getaddrinfo(host,port,&hints,&servinfo)!=0){
		perror("Could not get server addrinfo");
		exit(1);
	}

	int sockfd = socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol);
	if(sockfd<0){
		perror("Could not open socket");
		exit(1);
	}

	if(connect(sockfd,servinfo->ai_addr,servinfo->ai_addrlen)<0){
		perror("Connection failed");
		exit(1);
	}

	freeaddrinfo(servinfo);

	return sockfd;
}

int main(int argc,char* argv[]){
	if(argc!=3){
		fprintf(stderr,"Usage: %s <host> <port>",argv[0]);
		exit(1);
	}
	int servfd = connect_serv(argv[1],argv[2]);

	send(servfd,"cheese",6,0);
	send(servfd,"hello",5,0);
	char buf[20];
	recv(servfd,&buf,20,0);
	printf(buf);
}
