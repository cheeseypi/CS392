/*
 * =====================================================================================
 *
 *       Filename:  nsminishell.c
 *
 *    Description:  For this assignment, you will be adding to your mini bash shell to
 *    			make it more functional.
 *
 *    			Implement the following features:
 *
 *    	#		Backspace: Since you will not be using buffered input you will need
 *    					to re-implement the backspace key.
 *    	#		Left and Right Arrow Keys: should move the cursor back and forth.
 *    	---		Up and Down Arrow Keys: Should swap between previous and the current
 *    					command. For this feature you will most likely need to use
 *    					your linked list
 *
 *    	#		CTRL + "L": Clear the terminal except for the current command
 *    	#		CTRL + "A": Move to the start of the current command
 *    	#		CTRL + "E": Move to the end of the current command
 *    	---		CTRL + "W": Cut a word into the clipboard. You should be able to cut
 *    					multiple words. (Try using it in bash!)
 *    	---		CTRL + "U": Cut a line into the clipboard. It should be able to work
 *    					with the above commend. (Once again, try using it in bash)
 *    	---		CTRL + "Y": Paste.
 *
 *    	#		Color: Make it look pretty! The prompt and directory should be
 *    					different colors.
 *
 *    	#		Saved History: When you exit, save your command history to a file
 *    					called .nsmshistory and load the command history when you
 *    					start
 *    	---		Dollar Sign: Program the ability to use the $() to pass output from
 *    					one program into another (i.e. more $(myselect *.c))
 *
 *        Version:  1.0
 *        Created:  11/03/2017 01:33:14 AM
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
#include "list.h"
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

#define KEY_CTL_L 12
#define KEY_CTL_A 1
#define KEY_CTL_E 5
#define KEY_CTL_W 23
#define KEY_CTL_U 21
#define KEY_CTL_Y 25
#define KEY_BKSP 127
#define KEY_NL 10

typedef struct s_node* node;

static node history;
static int hisSize;
static int hisInd;

static node CurCMD;
static int curSize;
static int curInd;

static node CurCMDbk;
static int curSizebk;

static int running;

/* TODO
 * Implement Clipboard
 * Nested Commands
 * Fix U/D motion -- type, move up, edit command, enter -- duplicates command
 */

void exportHistory(){
	remove("./.nsmhistory");
	FILE* f = fopen("./.nsmhistory","w");
	node t = history;
	while(t){
		fprintf(f,"%s\n",(char*)t->elem);
		t=t->next;
	}
	fclose(f);
}

void importHistory(){
	int f;
	if((f = open("./.nsmhistory",O_RDONLY))<0){
		history=NULL;
		return;
	}
	char buf;
	int cursSize=0;
	char* curStr=(char*)malloc(sizeof(char)*cursSize);
	hisSize=0;
	hisInd=0;
	while(read(f,&buf,1)){
		if(buf=='\n'){
			hisSize++;
			hisInd++;
			cursSize++;
			curStr=(char*)realloc(curStr,sizeof(char)*cursSize);
			curStr[cursSize-1]='\0';
			append(new_node(curStr,NULL,NULL),&history);
			cursSize=0;
			curStr=(char*)malloc(sizeof(char)*cursSize);
		}
		else{
			cursSize++;
			curStr=(char*)realloc(curStr,sizeof(char)*cursSize);
			curStr[cursSize-1]=buf;
		}
	}
	close(f);
}

char* listToString(node head){
	node t = head;
	int strSize=0;
	char* str=(char*) malloc(sizeof(char)*strSize);
	while(t){
		strSize++;
		str = (char*) realloc(str,sizeof(char)*strSize);
		strcpy(&(str[strSize-1]),t->elem);
		t = t->next;
	}
	strSize++;
	str=(char*)realloc(str, sizeof(char)*strSize);
	strcpy(&(str[strSize-1]),"\0");
	return str;
}

node stringToList(char* str){
	node head = NULL;
	for(int ctr=0; str[ctr]!='\0'; ctr++){
		char* temp = (char*) malloc(sizeof(char));
		temp[0]=str[ctr];
		append(new_node(temp,NULL,NULL),&head);
	}
	return head;
}

void reprintCommand(){
	char* cmd = listToString(CurCMD);
	int index = curInd;
	while(curInd>0){//Move to start of current command
		int y,x;
		getyx(stdscr,y,x);
		if(x==0){
			int tmp = y;
			getmaxyx(stdscr,y,x);
			y = tmp-1;
			clrtoeol();
			while(mvgetch(y,x)==' '){
				if(x==0)
					break;
				x--;
			}
		}
		move(y,x-1);
		curInd--;
	}
	clrtoeol();//Clear whatever's printed
	addstr(cmd);//Reprint command
	curInd=strlen(cmd);
	while(curInd>index){//Move back to correct index
		int y,x;
		getyx(stdscr,y,x);
		if(x==0){
			int tmp = y;
			getmaxyx(stdscr,y,x);
			y = tmp-1;
			while(mvgetch(y,x)==' '){
				if(x==0)
					break;
				x--;
			}
		}
		move(y,x-1);
		curInd--;
	}
}

void miniprompt(){
	attron(COLOR_PAIR(1));
	addstr("(mini)");
	char cwd[1024];
	getcwd(cwd,sizeof(cwd));
	attron(COLOR_PAIR(2));
	addch(' ');
	addstr(cwd);
	attroff(COLOR_PAIR(2));
	addstr(" > ");
}

void minicd(char* path){
	if(chdir(path)!=0){
		addstr("Something went wrong.\n");
	}
}

void miniexit(){
	addstr("Goodbye\n");
	running=0;
}

void minihelp(){
	addstr("NSMinishell is a shell containing some very basic commands, listed here:\n");
	addstr("> cd : Usage: cd <path>. Can be used to move to relative or hard paths\n");
	addstr("> exit : Usage: exit. Can be used to exit minishell safely\n");
	addstr("> help : Usage: help. Displays this help message\n");
}

void miniexec(char* cmdStr){
	/*int y,maxy;
	y=getcury(stdscr);
	maxy=getmaxy(stdscr);
	if(y==maxy-1){
		addch('\n');
	}
	move(y+1,0);*/
	if(strlen(cmdStr)<1)
		return;
	char** cmd = my_str2vect(cmdStr);
	for(int ctr=0; cmd[ctr]; ctr++){
		if(strncmp(cmd[ctr],"$(",2)==0){
			perror("Subcommands not yet working");
			break;
		}
	}
	if(strcmp(cmd[0],"cd")==0)
		minicd(cmd[1]);
	else if(my_strcmp(cmd[0],"help")==0)
		minihelp();
	else if(my_strcmp(cmd[0],"exit")==0)
		miniexit();
	else{
		int outputfd[2];
		pipe(outputfd);
		int cpid = fork();
		if(cpid==0){
			close(outputfd[0]);
			dup2(outputfd[1],1);
			dup2(outputfd[1],2);
			signal(SIGINT,SIG_DFL);
			addstr("\n");
			if(execvp(cmd[0],cmd)!=1){
				my_str("Unrecognized.\n");
				minihelp();
			}
			close(outputfd[1]);
			exit(0);
		}
		else{
			close(outputfd[1]);
			char stdBuf;
			while(read(outputfd[0],&stdBuf,1))
				addch(stdBuf);
			wait(NULL);
		}
	}
}

int main(int argc, char* argv[]){
	importHistory();
	initscr();
	cbreak();
	noecho();
	if(has_colors()){
		start_color();
		if(can_change_color()){
			init_pair(1,COLOR_BLACK,COLOR_WHITE);
			init_pair(2,COLOR_GREEN,COLOR_BLACK);
		}
	}
	scrollok(stdscr,TRUE);
	keypad(stdscr,true);
	miniprompt();
	running=1;
	curSize=0;
	curInd=0;
	while(running){
		int c = getch();
		switch(c){
			case KEY_BKSP:
				if(curSize>0 && curInd>0){
					remove_node_at(&CurCMD,curInd-1);
					reprintCommand();
					curSize--;
					//curInd--;
				}
				break;
			case KEY_CTL_L:{//Clear term except for current command
				clear();
				miniprompt();
				char* tmp = listToString(CurCMD);
				addstr(tmp);
				free(tmp);
				break;}
			case KEY_CTL_A://Move to start of current command
				while(curInd>0){
					int y,x;
					getyx(stdscr,y,x);
					if(x==0){
						int tmp = y;
						getmaxyx(stdscr,y,x);
						y = tmp-1;
						while(mvgetch(y,x)==' '){
							if(x==0)
								break;
							x--;
						}
					}
					move(y,x-1);
					curInd--;
				}
				break;
			case KEY_CTL_E://Move to end of current command
				while(curInd<curSize){
					int y,x,maxx;
					getyx(stdscr,y,x);
					maxx=getmaxx(stdscr);
					if(x==maxx){
						y++;
						x=-1;
					}
					move(y,x+1);
					curInd++;
				}
				break;
			case KEY_CTL_W://Cut word into clipboard
				addstr("CutWord");
				break;
			case KEY_CTL_U://Cut line into clipboard
				addstr("CutLine");
				break;
			case KEY_CTL_Y://Paste
				addstr("Paste");
				break;
			case KEY_UP://Move up one command in the list
				if(hisInd>0 && hisInd==hisSize){//Backup current command
					CurCMDbk=CurCMD;
					curSizebk=curSize;
				}
				if(hisInd>0){//Load & display command
					hisInd--;
					node t = history;
					for(int ctr=0; ctr<hisInd; ctr++){
						t = t->next;
					}
					CurCMD=stringToList((char*)t->elem);
					reprintCommand();
					curSize=strlen(t->elem);
					while(curInd>0){//Move to start of command
						int y,x;
						getyx(stdscr,y,x);
						if(x==0){
							int tmp = y;
							getmaxyx(stdscr,y,x);
							y = tmp-1;
							while(mvgetch(y,x)==' '){
								if(x==0)
									break;
								x--;
							}
						}
						move(y,x-1);
						curInd--;
					}
					while(curInd<curSize){//Move to end of command
						int y,x,maxx;
						getyx(stdscr,y,x);
						maxx=getmaxx(stdscr);
						if(x==maxx){
							y++;
							x=-1;
						}
						move(y,x+1);
						curInd++;
					}
				}
				break;
			case KEY_DOWN://Move down one command in the list
				if(hisInd<hisSize){
					hisInd++;
					if(hisInd<hisSize){//Load from history
						node t = history;
						for(int ctr=0; ctr<hisInd; ctr++){
							t = t->next;
						}
						CurCMD=stringToList((char*)t->elem);
						reprintCommand();
						curSize=strlen(t->elem);
						while(curInd>0){//Move to start of command
							int y,x;
							getyx(stdscr,y,x);
							if(x==0){
								int tmp = y;
								getmaxyx(stdscr,y,x);
								y = tmp-1;
								while(mvgetch(y,x)==' '){
									if(x==0)
										break;
									x--;
								}
							}
							move(y,x-1);
							curInd--;
						}
						while(curInd<curSize){//Move to end of command
							int y,x,maxx;
							getyx(stdscr,y,x);
							maxx=getmaxx(stdscr);
							if(x==maxx){
								y++;
								x=-1;
							}
							move(y,x+1);
							curInd++;
						}
					}
					else if(hisInd==hisSize){//Load command in progress
						CurCMD = CurCMDbk;
						CurCMDbk = NULL;
						reprintCommand();
						curSize = curSizebk;
						curSizebk = 0;
						while(curInd>0){//Move to start of command
							int y,x;
							getyx(stdscr,y,x);
							if(x==0){
								int tmp = y;
								getmaxyx(stdscr,y,x);
								y = tmp-1;
								while(mvgetch(y,x)==' '){
									if(x==0)
										break;
									x--;
								}
							}
							move(y,x-1);
							curInd--;
						}
						while(curInd<curSize){//Move to end of command
							int y,x,maxx;
							getyx(stdscr,y,x);
							maxx=getmaxx(stdscr);
							if(x==maxx){
								y++;
								x=-1;
							}
							move(y,x+1);
							curInd++;
						}
					}
				}
				break;
			case KEY_LEFT:
				if(curInd>0){
					int y,x;
					getyx(stdscr,y,x);
					if(x==0){
						int tmp = y;
						getmaxyx(stdscr,y,x);
						y = tmp-1;
						while(mvgetch(y,x)=='\0'){
							if(x==0)
								break;
							x--;
						}
					}
					move(y,x-1);
					curInd--;
				}
				break;
			case KEY_RIGHT:
				if(curInd<curSize){
					int y,x,maxx;
					getyx(stdscr,y,x);
					maxx=getmaxx(stdscr);
					if(x==maxx){
						y++;
						x=-1;
					}
					move(y,x+1);
					curInd++;
				}
				break;
			case KEY_NL:
				{int y,maxy;
				y=getcury(stdscr);
				maxy=getmaxy(stdscr);
				if(y==maxy-1){
					addch('\n');
				}
				move(y+1,0);
				if(curSize>0){
					char* cmd = listToString(CurCMD);
					miniexec(cmd);
					append(new_node(cmd,NULL,NULL),&history);
					hisSize++;
					hisInd=hisSize;
					curSize=0;
					curInd=0;
					CurCMD=NULL;
				}
				if(CurCMDbk){
					CurCMDbk=NULL;
					curSize=0;
				}
				miniprompt();
				break;}
			default:
				{
				char* temp = (char*)malloc(sizeof(char));
				temp[0]=c;
				add_node_at(new_node(temp,NULL,NULL),&CurCMD,curInd);
				reprintCommand();
				curSize++;
				int y,x,maxx;
				getyx(stdscr,y,x);
				maxx=getmaxx(stdscr);
				if(x==maxx){
					y++;
					x=-1;
				}
				move(y,x+1);
				curInd++;
				break;}
		}
	}
	exportHistory();
	endwin();
}
