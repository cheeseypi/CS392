/*
 * =====================================================================================
 *
 *       Filename:  helpers.h
 *
 *    Description:  Helper functions for libmy. Serves to clean up code.
 *
 *        Version:  1.0
 *        Created:  09/01/2017 01:32:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Doto
 *   Organization:  
 *
 * =====================================================================================
 */

/* my_int */
int simple_pow(int num, int pow){
	if(pow==0){
		return 1;
	}
	else if(pow<0){
		return 0;
	}
	int rT = num;
	for(int c = 1; c<pow; c++){
		rT = rT*num;
	}
	return rT;
}
int simple_intlen(int num){
	int len = 1;
	while(num>=simple_pow(10,len)){
		len++;
	}
	return len;
}
