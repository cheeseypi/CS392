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

void child_handler(int signum){}

int main(int argc, char *argv[]){
	int pipefd[2];
	pid_t cpid;
	char buf;

	if(signal(SIGUSR1, child_handler) == SIG_ERR){
		my_str("Can't catch SIGUSR1");
		exit(1);
	}

	if(pipe(pipefd)==-1)
		exit(1);

	if((cpid = fork())==-1)
		exit(1);

	if(cpid == 0){
		int gcpipefd[2];
		pid_t gcpid;
		
		if(pipe(gcpipefd)==-1)
			exit(1);

		if((gcpid = fork()) == -1)
			exit(1);

		if(gcpid == 0){//GRANDCHILD PROCESS
			pause();
			my_str("Grandchild: ");
			close(gcpipefd[1]);
			while (read(gcpipefd[0], &buf, 1) > 0){
				write(1, &buf, 1);
			}
			my_char('\n');
			close(gcpipefd[0]);
			exit(0);
		} else {//CHILD PROCESS
			pause();
			my_str("Child: ");
			close(pipefd[1]);
			close(gcpipefd[0]);
			while (read(pipefd[0], &buf, 1) > 0){
				write(1, &buf, 1);
				write(gcpipefd[1], &buf, 1);
			}
			my_char('\n');
			kill(gcpid, SIGUSR1);
			close(pipefd[0]);
			close(gcpipefd[1]);
			wait(NULL);
			exit(0);
		}
	} else { //PARENT PROCESS
		my_str("Parent: ");
		my_str(my_vect2str(&argv[1]));
		my_char('\n');
		kill(cpid, SIGUSR1);
		close(pipefd[0]);
		write(pipefd[1],my_vect2str(&argv[1]),my_strlen(my_vect2str(&argv[1])));
		close(pipefd[1]);
		wait(NULL);
		exit(0);
	}
}
