/*
 * =====================================================================================
 *
 *       Filename:  socket_server.c
 *
 *    Description:  Sockettalk Server
 *
 *        Version:  1.0
 *        Created:  11/15/2017 02:10:25 PM
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
#include <fcntl.h>
#include <unistd.h>

int start_serv(char* port){
	struct addrinfo hints, *servinfo;

	memset(&hints, 0, sizeof hints);
	hints.ai_family=AF_INET;
	hints.ai_socktype=SOCK_STREAM;

	if(getaddrinfo("0.0.0.0",port,&hints,&servinfo)!=0){
		perror("Could not get local addrinfo");
		exit(1);
	}
	printf("Got addr info...\n");

	int sockfd = socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol);
	if(sockfd<0){
		perror("Could not open socket");
		exit(1);
	}
	printf("Got sock info...\n");

	fcntl(sockfd,F_SETFL,fcntl(sockfd,F_GETFL,0) | O_NONBLOCK);

	//Handle socket-in-use
	int yes=1;
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes)==-1){
		perror("Setsockopt");
		exit(1);
	}

	bind(sockfd,servinfo->ai_addr,servinfo->ai_addrlen);
	printf("Bound socket...\n");

	freeaddrinfo(servinfo);

	return sockfd;
}

int main(int argc, char* argv[]){
	if(argc!=2){
		fprintf(stderr,"Usage: %s <port>",argv[0]);
		exit(1);
	}
	nfds_t numClients = 0;
	char* clientnicks[FD_SETSIZE] = {NULL};
	struct pollfd clientfds[FD_SETSIZE];
	for(int i = 0; i<FD_SETSIZE; i++)
		clientfds[i].fd=-1;
	printf("Initialized client vars...\n");
	int servfd = start_serv(argv[1]);
	printf("Server started...\n");
	listen(servfd,FD_SETSIZE);
	printf("Connector found...\n");

	while(1){
		if((clientfds[numClients].fd = accept(servfd,NULL,NULL))!=-1){
			printf("Accepting client...\n");
			clientfds[numClients].events = POLLIN | POLLOUT;
			clientnicks[numClients] = "";
			numClients++;
		}
		poll(clientfds,numClients,0);
		for(int i=0; i<numClients; i++){
			if(clientfds[i].fd==-1)
				continue;
			if(clientfds[i].revents & (POLLERR | POLLHUP | POLLNVAL)){
				printf("Client disconnected...\n");
				clientfds[i].fd=-1;
			}
			else if(clientfds[i].revents & POLLIN){
				printf("Message received...\n");
				char buf;
				int currentSize = 0;
				char* msg = (char*) malloc(sizeof(char)*currentSize);
				while(recv(clientfds[i].fd,&buf,1,0)){
					currentSize++;
					msg = (char*) realloc(msg,sizeof(char)*currentSize);
					msg[currentSize-1]=buf;
					if(buf=='\n' || buf=='\0'){
						msg[currentSize-1]='\0';
						break;
					}
				}
				printf("msg: %s\n",msg);

				int good = 0;
				for(int i = 0; i<currentSize; i++){
					if(msg[i]<=126 && msg[i]>=33){
						good = 1;
						break;
					}
				}
				if(!good)
					continue;
				
				if(strlen(clientnicks[i])==0){
					printf("Setting nick...\n");
					if(strncmp("/nick",msg,5)==0){
						clientnicks[i] = (char*) malloc(sizeof(char)*strlen(msg)-6);
						strcpy(clientnicks[i],&(msg[6]));
					}
					else{
						clientnicks[i] = (char*) malloc(sizeof(char)*strlen(msg));
						strcpy(clientnicks[i],msg);
					}
				}
				else if(strncmp("/nick",msg,5)==0){
					printf("Setting nick...\n");
					clientnicks[i] = (char*) malloc(sizeof(char)*strlen(msg)-6);
					strcpy(clientnicks[i],&(msg[6]));
				}
				else if(strncmp("/exit",msg,5)==0){
					printf("Disconnecting client...\n");
					close(clientfds[i].fd);
					clientfds[i].fd=-1;
				}
				else if(strncmp("/me",msg,3)==0){
					printf("Sending as me...\n");
					char* sendMsg = (char*) malloc(sizeof(char)*(strlen(clientnicks[i])+1+strlen(msg)+1));
					strcpy(sendMsg,clientnicks[i]);
					strcat(sendMsg," ");
					strcat(sendMsg,&(msg[4]));
					strcat(sendMsg,"\n");

					for(int j=0; j<numClients; j++){
						if(clientfds[j].fd!=-1 && (clientfds[j].revents & POLLOUT)){
							send(clientfds[j].fd,sendMsg,strlen(sendMsg),0);
						}
					}

					free(sendMsg);
				}
				else{
					printf("Sending as normal...\n");
					char* sendMsg = (char*) malloc(sizeof(char)*(strlen(clientnicks[i])+2+strlen(msg)+1));
					strcpy(sendMsg,clientnicks[i]);
					strcat(sendMsg,": ");
					strcat(sendMsg,msg);
					strcat(sendMsg,"\n");

					for(int j=0; j<numClients; j++){
						if(clientfds[j].fd!=-1 && (clientfds[j].revents & POLLOUT)){
							send(clientfds[j].fd,sendMsg,strlen(sendMsg),0);
						}
					}

					free(sendMsg);
				}
			}
		}
	}
}
