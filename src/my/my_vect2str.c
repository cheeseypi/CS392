/*
 * =====================================================================================
 *
 *       Filename:  my_vect2str.c
 *
 *    Description:  Takes a vector (array of string ended by a NULL)
 *    			Allocates a new string and copies each string from the array into
 *    			new string separated by a single space, until NULL pointer to string
 *    			is found.
 *    			Returns new string.
 *    			i.e. {"hello","world",NULL} -> "hello world";
 *
 *        Version:  1.0
 *        Created:  10/06/2017 01:03:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Doto (), mvd369@gmail.com
 *   Organization:  
 *                  I Pledge My Honor That I Have Abided By The Stevens Honor System
 *
 * =====================================================================================
 */
#include "my.h"

char* my_vect2str(char** x){
	int totalSize = 0;
	int ctr=0;
	for(char* t = x[ctr]; t; t = x[ctr]){
		totalSize+=my_strlen(t)+1;
		ctr++;
	}
	char* rT = (char*) malloc(sizeof(char*)*totalSize);
	my_strcpy(rT,"\0");
	ctr=0;
	for(char* t = x[ctr]; t; t = x[ctr]){
		my_strcat(rT, t);
		if(x[ctr+1])
			my_strcat(rT," ");
		ctr++;
	}
}
