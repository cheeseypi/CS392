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

char** create_vector(char* str){
	int count = 0;
	int inWord = 0;
	for(int ind = 0; str[ind]!='\0'; ind++){
		if(str[ind]==' ' || str[ind]=='\t' || str[ind]=='\n'){
			inWord = 0;
		}
		else if(!inWord){
			inWord = 1;
			count++;
		}
	}
	return (char**) malloc(sizeof(char*)*count);
}

void malloc_vector(char* str, char** vect){
	int vectInd = 0;
	int sizeofcurword = 0;
	int inWord = 0;
	for(int ind = 0; str[ind]!='\0'; ind++){
		if(str[ind]==' ' || str[ind]=='\t' || str[ind]=='\n'){
			if(inWord){
				vect[vectInd] = (char*) malloc(sizeofcurword*sizeof(char));
				vectInd++;
				sizeofcurword=0;
			}
			inWord = 0;
		}
		else{
			sizeofcurword++;
			inWord = 1;
		}
	}
	if(sizeofcurword>0)
		vect[vectInd] = (char*) malloc(sizeofcurword*sizeof(char));
}

void fill_vector(char* str, char** vect){
	int vectInd = 0;
	int charInd = 0;
	int inWord = 0;
	for(int ind = 0; str[ind]!='\0'; ind++){
		if(str[ind]==' ' || str[ind]=='\t' || str[ind]=='\n'){
			if(inWord){
				vectInd++;
				charInd = 0;
			}
			inWord = 0;
		}
		else{
			vect[vectInd][charInd]=str[ind];
			charInd++;
			inWord = 1;
		}
	}
}

char** my_str2vect(char* str){
	char** vect = create_vector(str);
	malloc_vector(str, vect);
	fill_vector(str, vect);
	return vect;
}
