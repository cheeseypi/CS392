#include "my.h"

int my_atoi(char* str){
	int num = 0;
	int sign = 1;
	int ctr = 0;
	int len = my_strlen(str);
	while(ctr<len && (str[ctr]-'0'<0 || str[ctr]-'0'>9)){
		if(str[ctr] == '-')
			sign *= -1;
		ctr++;
	}
	while(ctr<len && str[ctr]-'0'>=0 && str[ctr]-'0'<=9){
		num = num * 10;
		num+=str[ctr]-'0';
		ctr++;
	}
	return sign * num;
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
