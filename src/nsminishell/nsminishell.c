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
#include <signal.h>

#define KEY_CTL_L 12
#define KEY_CTL_A 1
#define KEY_CTL_E 5
#define KEY_CTL_W 23
#define KEY_CTL_U 21
#define KEY_CTL_Y 25
#define KEY_BKSP 127

typedef struct s_node* node;

//static node StartOfList;
//static node CurCMD;

static int running;

/* TODO
 * Implement command chain linkedlist
 * Implement currentcommand char*
 * Implement running commands
 * Implement L/R motion restrictions
 * Implement clearing terminal, moving to 0, moving to $
 * Implement U/D motion
 * Implement Clipboard
 */

void miniprompt(){
	beep();
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
	//Export to .nsmhistory
	running=0;
}

void minihelp(){
	addstr("Minishell is a shell containing some very basic commands, listed here:\n");
	addstr("> cd : Usage: cd <path>. Can be used to move to relative or hard paths\n");
	addstr("> exit : Usage: exit. Can be used to exit minishell safely\n");
	addstr("> help : Usage: help. Displays this help message\n");
}

void exportHistory(node head){

}

void importHistory(node head){

}

int main(int argc, char* argv[]){
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
	
	keypad(stdscr,true);
	miniprompt();
	running=1;
	while(running){
		int c = getch();
		switch(c){
			case KEY_BKSP:
				{int y,x;
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
				//Remove char from current command
				break;}
			case KEY_CTL_L://Clear term except for current command
				addstr("Clear");
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
			case 10:
				{int y,x;
				getyx(stdscr,y,x);
				move(y+1,x-x);
				miniprompt();
				break;}
			default:
				addch(c);
				//Add char to current command
				break;
		}
	}
	endwin();
}
