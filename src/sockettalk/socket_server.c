/*
 * =====================================================================================
 *
 *       Filename:  socket_server.c
 *
 *    Description:  Chat Server
 *
 *        Version:  1.0
 *        Created:  10/30/2017 12:48:21 PM
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE 500

int main(int argc, char *argv[])
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s;
	struct sockaddr_in peer_addr;
	socklen_t peer_addr_len;
	ssize_t nread;
	char buf[BUF_SIZE];

	if (argc != 2) {
		fprintf(stderr, "Usage: %s port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;	 /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;	 /* For wildcard IP address */
	hints.ai_protocol = 0;			/* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	s = getaddrinfo(NULL, argv[1], &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
		Try each address until we successfully bind(2).
		If socket(2) (or bind(2)) fails, we (close the socket
		and) try the next address. */

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype,
				rp->ai_protocol);
		if (sfd == -1)
			continue;

		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;					/* Success */

		close(sfd);
	}

	if (rp == NULL) {				/* No address succeeded */
		fprintf(stderr, "Could not bind\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result);			/* No longer needed */

	int users_size=0;
	char** users;
	int peer_addrs_size=0;
	struct sockaddr_in* peer_addrs;
	users = (char**) malloc(sizeof(char*)*users_size);
	peer_addrs = (struct sockaddr_in*) malloc(sizeof(struct sockaddr)*peer_addrs_size);

	/* Read datagrams and echo them back to sender */

	while(1) {
		peer_addr_len = sizeof(struct sockaddr_in);
		nread = recvfrom(sfd, buf, BUF_SIZE, 0,
				(struct sockaddr *) &peer_addr, &peer_addr_len);
		if (nread == -1)
			continue;				/* Ignore failed request */

		if(strncmp(buf,"/nick",5)==0){
			int inList = 0;
			int i = 0;
			for(; i<peer_addrs_size; i++){
				if(peer_addr.sin_addr.s_addr==peer_addrs[i].sin_addr.s_addr){
					inList=1;
					break;
				}
			}
			if(!inList){
				peer_addrs_size++;
				peer_addrs = (struct sockaddr_in*) realloc(peer_addrs,sizeof(struct sockaddr)*peer_addrs_size);
				users_size++;
				users = (char**) realloc(users,sizeof(char*)*users_size);
			}
			peer_addrs[i]=peer_addr;
			int len = strlen(&buf[6]);
			users[i]=(char*)malloc(len*sizeof(char));
			strncpy(users[i],&buf[6],len);
		}
		if(strncmp(buf,"/exit",5)==0){
			int inList = 0;
			int i = 0;
			for(; i<peer_addrs_size; i++){
				if(peer_addr.sin_addr.s_addr==peer_addrs[i].sin_addr.s_addr){
					inList=1;
					break;
				}
			}
			if(inList){
				for(int ctr = i; ctr<peer_addrs_size-1; ctr++){
					peer_addrs[ctr]=peer_addrs[ctr+1];
				}
				peer_addrs_size--;
				for(int ctr = i; ctr<users_size-1; ctr++){
					users[ctr]=users[ctr+1];
				}
				users_size--;
				free(users[users_size]);
				users = (char**) realloc(users,sizeof(char*)*users_size);
			}
		}

		char host[NI_MAXHOST], service[NI_MAXSERV];

		s = getnameinfo((struct sockaddr *) &peer_addr,
						peer_addr_len, host, NI_MAXHOST,
						service, NI_MAXSERV, NI_NUMERICSERV);
		if (s == 0)
			printf("Received %zd bytes from %s:%s\n",
					nread, host, service);
		else
			fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

		if (sendto(sfd, buf, nread, 0,
			(struct sockaddr *) &peer_addr,
			peer_addr_len) != nread)
			fprintf(stderr, "Error sending response\n");
	}
}
