/*
 * =====================================================================================
 *
 *       Filename:  minishell.c
 *
 *    Description:  A very basic miniature shell, emulating some basic features of bash
 *
 *        Version:  1.0
 *        Created:  10/13/2017 01:45:09 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Doto (), mvd369@gmail.com
 *   Organization:  
 *                  I Pledge My Honor That I Have Abided By The Stevens Honor System
 *
 * =====================================================================================
 */
#define _POSIX_SOURCE
#include "my.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void miniprompt(){
	my_str("(mini) ");
	char cwd[1024];
	getcwd(cwd,sizeof(cwd));
	my_str(cwd);
	my_str(" > ");
}

void minicd(char* path){
	if(chdir(path)!=0){
		my_str("Something went wrong.\n");
	}
}

void miniexit(){
	my_str("Goodbye\n");
	exit(0);
}

void minihelp(){
	my_str("Minishell is a shell containing some very basic commands, listed here:\n");
	my_str("> cd : Usage: cd <path>. Can be used to move to relative or hard paths\n");
	my_str("> exit : Usage: exit. Can be used to exit minishell safely\n");
	my_str("> help : Usage: help. Displays this help message\n");
}

static pid_t cpid;

void sighand(int signo){
	kill(cpid,SIGINT);
}

int main(int argc, char* argv[]){
	char buf[255];
	signal(SIGINT,sighand);
	while(1){	
		miniprompt();
		read(0,&buf,255);
		char** cmd = my_str2vect(buf);
		if(my_strcmp(cmd[0],"cd")==0)
			minicd(cmd[1]);
		else if(my_strcmp(cmd[0],"help")==0)
			minihelp();
		else if(my_strcmp(cmd[0],"exit")==0)
			miniexit();
		else{
			cpid = fork();
			if(cpid==0){
				if(execv(cmd[0],&(cmd[1]))!=1){
					my_str("Unrecognized.\n");
					minihelp();
				}
				exit(0);
			}
			else{
				wait(NULL);
			}
		}
		for(int i = 0; i<255; i++)
			buf[i]='\0';
	}
}
