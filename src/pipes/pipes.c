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
#include <unistd.h>
#include "my.h"

