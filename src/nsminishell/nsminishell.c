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
 *    			Backspace: Since you will not be using buffered input you will need
 *    					to re-implement the backspace key.
 *    			Left and Right Arrow Keys: should move the cursor back and forth.
 *    			Up and Down Arrow Keys: Should swap between previous and the current
 *    					command. For this feature you will most likely need to use
 *    					your linked list
 *
 *    			CTRL + "L": Clear the terminal except for the current command
 *    			CTRL + "A": Move to the start of the current command
 *    			CTRL + "E": Move to the end of the current command
 *    			CTRL + "W": Cut a word into the clipboard. You should be able to cut
 *    					multiple words. (Try using it in bash!)
 *    			CTRL + "U": Cut a line into the clipboard. It should be able to work
 *    					with the above commend. (Once again, try using it in bash)
 *    			CTRL + "Y": Paste.
 *
 *    			Color: Make it look pretty! The prompt and directory should be
 *    					different colors.
 *
 *    			Saved History: When you exit, save your command history to a file
 *    					called .nsmshistory and load the command history when you
 *    					start
 *    			Dollar Sign: Program the ability to use the $() to pass output from
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

static node StartOfList;
static node CurCMD;
static int curSize;

static int running;

/* TODO
 * Implement command chain linkedlist -- BACKSPACE REMOVING CHARS
 * Implement L/R motion restrictions
 * Implement clearing terminal, moving to 0, moving to $
 * Implement U/D motion
 * Implement Clipboard
 */

void exportHistory(){
	remove("./.nsmhistory");
	FILE* f = fopen("./.nsmhistory","w");
	node t = StartOfList;
	while(t){
		fprintf(f,"\n%s",(char*)t->elem);
		t=t->next;
	}
	fclose(f);
}

void importHistory(){
	int f;
	if((f = open("./.nsmhistory",O_RDONLY))<0){
		curSize=0;
		CurCMD=new_node((char*)malloc(sizeof(char)*curSize),NULL,NULL);
		append(CurCMD,&StartOfList);
		return;
	}
	char buf;
	char* curStr;
	curSize=0;
	while(read(f,&buf,1)){
		if(buf=='\n'){
			curSize=0;
			curStr=(char*)malloc(sizeof(char)*curSize);
			CurCMD=new_node(curStr,NULL,NULL);
			append(CurCMD,&StartOfList);
		}
		else{
			curSize++;
			curStr=(char*)realloc(curStr,sizeof(char)*curSize);
			curStr[curSize-1]=buf;
		}
	}
	curSize=0;
	CurCMD=new_node((char*)malloc(sizeof(char)*curSize),NULL,NULL);
	append(CurCMD,&StartOfList);
	close(f);
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
	exportHistory();
	running=0;
}

void minihelp(){
	addstr("Minishell is a shell containing some very basic commands, listed here:\n");
	addstr("> cd : Usage: cd <path>. Can be used to move to relative or hard paths\n");
	addstr("> exit : Usage: exit. Can be used to exit minishell safely\n");
	addstr("> help : Usage: help. Displays this help message\n");
}

void miniexec(char* cmdStr){
	int y,maxy;
	y=getcury(stdscr);
	maxy=getmaxy(stdscr);
	if(y==maxy-1){
		addch('\n');
	}
	move(y+1,0);
	if(strlen(cmdStr)<1)
		return;
	char** cmd = my_str2vect(cmdStr);
	if(strcmp(cmd[0],"cd")==0)
		minicd(cmd[1]);
	else if(my_strcmp(cmd[0],"help")==0)
		minihelp();
	else if(my_strcmp(cmd[0],"exit")==0)
		miniexit();
	else{
		int pipefd[2];
		pipe(pipefd);
		int cpid = fork();
		if(cpid==0){
			close(pipefd[0]);
			dup2(pipefd[1],1);
			dup2(pipefd[1],2);
			signal(SIGINT,SIG_DFL);
			if(execvp(cmd[0],cmd)!=1){
				my_str("Unrecognized.\n");
				minihelp();
			}
			close(pipefd[1]);
			exit(0);
		}
		else{
			close(pipefd[1]);
			char stdbuf;
			while(read(pipefd[0],&stdbuf,1))
				addch(stdbuf);
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
	while(running){
		int c = getch();
		switch(c){
			case KEY_BKSP:
				{
				if(curSize>0){
					curSize--;
					((char*)CurCMD->elem)[curSize]='\0';
				}
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
				//Restrict motion to within command
				delch();
				break;}
			case KEY_CTL_L://Clear term except for current command
				clear();
				miniprompt();
				addstr((char*)CurCMD->elem);
				break;
			case KEY_CTL_A://Move to start of current command
				addstr("MoveTo0");
				break;
			case KEY_CTL_E://Move to end of current command
				addstr("MoveTo$");
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
				addstr("Up");
				break;
			case KEY_DOWN://Move down one command in the list
				addstr("Down");
				break;
			case KEY_LEFT:
				{int y,x;
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
				//Restrict motion to within command
				break;}
			case KEY_RIGHT:
				{int y,x;
				getyx(stdscr,y,x);
				move(y,x+1);
				//Restrict motion to within command
				break;}
			case KEY_NL:
				{
				if(strlen(CurCMD->elem)>0){
					curSize++;
					CurCMD->elem = (char*)realloc(CurCMD->elem,sizeof(char)*curSize);
					((char*)(CurCMD->elem))[curSize-1]='\0';
					miniexec(CurCMD->elem);
					curSize=0;
					CurCMD=new_node((char*)malloc(sizeof(char)*curSize),NULL,NULL);
					append(CurCMD,&StartOfList);
				}
				int y,maxy;
				y=getcury(stdscr);
				maxy=getmaxy(stdscr);
				if(y==maxy-1){
					addch('\n');
				}
				move(y+1,0);
				miniprompt();
				break;}
			default:
				addch(c);
				curSize++;
				CurCMD->elem = (char*)realloc(CurCMD->elem,sizeof(char)*curSize);
				((char*)(CurCMD->elem))[curSize-1]=c;
				break;
		}
	}
	endwin();
}
