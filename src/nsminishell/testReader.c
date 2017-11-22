/*
 * =====================================================================================
 *
 *       Filename:  testReader.c
 *
 *    Description:  Reads from stdin
 *
 *        Version:  1.0
 *        Created:  11/16/2017 06:17:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Doto (), mvd369@gmail.com
 *   Organization:  
 *                  I Pledge My Honor That I Have Abided By The Stevens Honor System
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(){
	char buf;
	while(read(0,&buf,1)){
		write(1,&buf,1);
		if(buf=='\n')
			break;
	}
}
