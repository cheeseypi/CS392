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
#include <unistd.h>

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
	struct pollfd servstdin[2];
	servstdin[0].fd = connect_serv(argv[1],argv[2]);
	servstdin[0].events = POLLIN | POLLOUT;
	servstdin[1].fd = 0;
	servstdin[1].events = POLLIN;

	write(1,"Nickname: ",10);
	int running = 1;
	while(running){
		poll(servstdin,2,0);
		if(servstdin[0].revents & POLLIN){
			char buf;
			int curSize=0;
			char* msg = (char*) malloc(sizeof(char)*curSize);
			while(recv(servstdin[0].fd,&buf,1,0)){
				curSize++;
				msg = (char*) realloc(msg,sizeof(char)*curSize);
				msg[curSize-1]=buf;
				if(buf=='\n' || buf=='\0'){
					msg[curSize-1]='\0';
					break;
				}
			}
			printf("%s\n",msg);
			free(msg);
		}
		if((servstdin[1].revents & POLLIN) && (servstdin[0].revents & POLLOUT)){
			char buf;
			int curSize=0;
			char* msg = (char*) malloc(sizeof(char)*curSize);
			while(read(servstdin[1].fd,&buf,1)){
				curSize++;
				msg = (char*) realloc(msg,sizeof(char)*curSize);
				msg[curSize-1]=buf;
				if(buf=='\n' || buf=='\0'){
					msg[curSize-1]='\n';
					break;
				}
			}
			if(strncmp(msg,"/exit",5)==0)
				running = 0;
			send(servstdin[0].fd,msg,curSize,0);
			free(msg);
		}
	}
	close(servstdin[0].fd);

	/*Test program
	send(servfd,"/nick cheese\n",13,0);
	send(servfd,"/me waves\n",10,0);
	char buf;
	int curSize=0;
	char* msg = (char*) malloc(sizeof(char)*curSize);
	while(recv(servfd,&buf,1,0)){
		curSize++;
		msg = (char*) realloc(msg,sizeof(char)*curSize);
		msg[curSize-1]=buf;
		if(buf=='\n' || buf=='\0'){
			msg[curSize-1]='\0';
			break;
		}
	}
	printf("%s\n",msg);
	send(servfd,"/exit\n",6,0);*/
}
