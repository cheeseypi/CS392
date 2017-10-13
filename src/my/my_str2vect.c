/*
 * =====================================================================================
 *
 *       Filename:  my_str2vect.c
 *
 *    Description:  Takes a string 
 *    			Allocates a new vector (array of string ended by a NULL), 
 *    			Splits apart the input string x at each space character 
 *    			Returns the newly allocated array of strings
 *    			Any number of ' ','\t', and '\n's can separate words.
 *    			I.e. "hello \t\t\n class,\nhow are you?" ->
 *    			{"hello", "class,", "how", "are","you?", NULL}
 *
 *        Version:  1.0
 *        Created:  10/12/2017 09:59:30 PM
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

int getNumWords(char* str){
	char c=str[0];
	int count = 0;
	int inWord = 0;
	for(int ctr=1; c!='\0'; (c=str[ctr], ctr++)){
		if(c==' ' || c=='\t' || c=='\n'){
			inWord=0;
		}
		else if(!inWord){
			count++;
			inWord=1;
		}
	}
}

char** my_str2vect(char* str){
	int numWords = getNumWords(str);
	int lengths[numWords];
	char c = str[0];
	int lengthInd = 0;
	int length = 0;
	int inWord = 0;
	for(int charctr = 1; c!='\0'; (c = str[charctr], charctr++)){
		if((c==' ' || c=='\t' || c=='\n') && inWord){
			lengths[lengthInd] = length;
			lengthInd++;
			length=0;
			inWord=0;
		}
		else if(c==' ' || c=='\t' || c=='\n'){
			inWord=0;
		}
		else if(!inWord){
			inWord=1;
			length++;
		}
		else{
			length++;
		}
	}

	char** rT = (char**) malloc(sizeof(char*)*numWords);
	for(int i = 0; i<numWords; i++)
		rT[i] = (char*) malloc(sizeof(char)*lengths[i]);
	
	c = str[0];
	inWord = 0;
	int word = 0;
	int charInd = 0;
	for(int charctr = 1; c!='\0'; (c = str[charctr], charctr++)){
		if((c==' ' || c=='\t' || c=='\n') && inWord){
			inWord = 0;
			word++;
			charInd=0;
		}
		else if(c==' ' || c=='\t' || c=='\n'){
			inWord=0;
		}
		else{
			inWord=1;
			rT[word][charInd]=c;
			charInd++;
		}
	}
}
