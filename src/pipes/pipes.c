/*
 * =====================================================================================
 *
 *       Filename:  pipes.c
 *
 *    Description:  Create a program that follows this basic workflow:
 *    				• A main function should creates a pipe to communicate from it
 *    					to a forked child process.
 *    				• A child process should also create a different pipe to
 *    					communicate from it to a "grandchild" process (i.e. create
 *    					a fork within the child process).
 *    				• The main program should take the command line arguments and
 *    					send them as a string across the pipe to the child.
 *    				• The child process should print out the message and then take
 *    					the text from the first pipe and pass it along the second
 *    					pipe to the grandchild.
 *    				• The "grandchild" process should take text from the second
 *    					pipe and print it out.
 *    			The final output should look like:
 *    				$./pipes hello world
 *    				$Parent: hello world
 *    				$Child: hello world
 *    				$Grandchild: hello world
 *    			All processes must wait for their children to complete before ending
 *    				to prevent creation of zombies.
 *
 *    			If no command line arguments are provided, you must display a usage
 *    				message instead and terminate without creating any new
 *    				processes.
 *
 *    			You may make the assumption that any test argument will be small
 *    				enough that a single read() will be enough to read in the
 *    				entire argument from the pipe as long as you allocate a buffer
 *    				of at least 100 bytes.
 *
 *    			Hint: Open file descriptors are maintained across forks.
 *
 *    			The important things on which you will be graded are correctly
 *    				creating a grandchild process (not two children), correctly
 *    				reading/writing the string to children by piping, error
 *    				checking all system calls, and creating an application
 *    				(not a library).
 *
 *        Version:  1.0
 *        Created:  10/06/2017 12:54:02 PM
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
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "my.h"

int main(int argc, char *argv[]){
	if(argc<=1){
		my_str("Usage: ./pipes <string> [string] [string] ...\n");
		exit(1);
	}

	int pipefd[2];
	pid_t cpid;

	my_str("Parent: ");
	my_str(my_vect2str(&argv[1]));
	my_char('\n');

	if(pipe(pipefd)==-1){
		my_str("Failed to create pipe\n");
		exit(1);
	}

	if((cpid = fork())==-1){
		my_str("Failed to fork\n");
		exit(1);
	}

	if(cpid == 0){
		char buf[100];
		my_str("Child: ");
		close(pipefd[1]);
		read(pipefd[0], &buf, 100);
		close(pipefd[0]);
		my_str(buf);
		my_char('\n');

		int gcpipefd[2];
		pid_t gcpid;
		
		if(pipe(gcpipefd)==-1){
			my_str("Failed to create pipe\n");
			exit(1);
		}

		if((gcpid = fork()) == -1){
			my_str("Failed to fork\n");
			exit(1);
		}

		if(gcpid == 0){//GRANDCHILD PROCESS
			my_str("Grandchild: ");
			close(gcpipefd[1]);
			read(gcpipefd[0], &buf, 100);
			my_str(buf);
			my_char('\n');
			close(gcpipefd[0]);
			exit(0);
		} else {//CHILD PROCESS
			close(gcpipefd[0]);
			write(gcpipefd[1],&buf,100);
			close(gcpipefd[1]);
			wait(NULL);
			exit(0);
		}
	} else { //PARENT PROCESS
		close(pipefd[0]);
		write(pipefd[1],my_vect2str(&argv[1]),my_strlen(my_vect2str(&argv[1])));
		close(pipefd[1]);
		wait(NULL);
		exit(0);
	}
}
