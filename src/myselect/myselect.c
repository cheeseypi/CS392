/*
 * =====================================================================================
 *
 *       Filename:  myselect.c
 *
 *    Description:  You will clear the terminal and display a list of all the strings
 *    			passed formatted into columns. The columns should fit the entirety
 *    			of every string.
 *
 *    			If there is not enough room for all items, clear the screen and
 *    			display "please enlarge the window" until the window is large
 *    			enough.
 *
 *    			Every time the window size changes, re-display the items to
 *    			accommodate to the new size.
 *
 *    			The first item should be underlined.
 *
 *    			Using the keyboard:
 *    			- Space key: Used to select/deselect
 *    			If the item was not highlighted, this will highlight it and move the
 *    			underline to the next item, wrapping around if necessary.
 *    			If the item was already highlighted, remove the highlight and stay
 *    			there.
 *
 *    			- ESC: Restore the display and exit
 *
 *    			- Enter: Restore everything and print onto the standard output the
 *    			list of all items that are currently highlighted (with a whitespace
 *    			between each one)
 *
 *    			- Up arrow: move to the previous item, wrap around if necessary
 *    			(i.e. pressing up when on the first item will move the underline to
 *    			the last item)
 *
 *    			- Down arrow: move to the next item, wrap around if necessary
 *
 *    			- Left arrow: move to the item on same row but previous column. If
 *    			you are on the first column, jump to the first item. DO NOT wrap
 *    			around.
 *
 *    			- Right arrow: move to the item on the same row but next column. If
 *    			you are on the last column, jump to the last item. DO NOT wrap
 *    			around.
 *
 *    			The other keys (including control-C) should have no effect.
 *
 *        Version:  1.0
 *        Created:  12/01/2017 12:00:07 AM
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
#include <stdlib.h>
#include <stdio.h>
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

typedef struct file_display{
	int isSelected;
	char* filename;
	int nameLen;
}* FileDisp;

static FileDisp* fileList;
static int highlighted,size;
static int width,height;

FileDisp init_filedisp(char* filename){
	FileDisp fd = (FileDisp) malloc(sizeof(struct file_display));
	fd->isSelected = 0;
	fd->filename = filename;
	fd->nameLen = strlen(filename);
	return fd;
}

void refreshDispSize(){
	struct winsize size;
	ioctl(fileno(stdout),TIOCGWINSZ,&size);
	width = size.ws_col;
	height = size.ws_row;
}

int redrawTable(){
	clear();
	move(0,0);
	int maxThisCol = 0;
	for(int i = 0; i<size; i++){
		if(fileList[i]->nameLen > maxThisCol)//Keep up with max length
			maxThisCol = fileList[i]->nameLen;
		if(getcurx(stdscr)+(fileList[i]->nameLen)+1>width){
			return -1;
		}
		if(i==highlighted)
			attron(A_UNDERLINE);
		if(fileList[i]->isSelected){
			attroff(COLOR_PAIR(2));//Turn off background
			attron(COLOR_PAIR(1));//Turn on highlight
		}

		addstr(fileList[i]->filename);
		move(getcury(stdscr),getcurx(stdscr)-(fileList[i]->nameLen));

		attroff(A_UNDERLINE);
		attroff(COLOR_PAIR(1));//Turn off highlight
		attron(COLOR_PAIR(2));//Turn on background

		if(getcury(stdscr)>=height-1){//If at end, move to next row
			int x = getcurx(stdscr);
			if(x+maxThisCol+2>width && i!=size-1){
				return -1;
			}
			move(0,x+maxThisCol+1);
			maxThisCol = 0;
		}
		else{//Otherwise, move down one
			move(getcury(stdscr)+1,getcurx(stdscr));
		}
	}
	return 0;
}

int main(int argc, char* argv[]){
	if(argc<2){
		perror("Usage: %s <filenames>");
		exit(1);
	}
	//Initialize big filelist
	size=0;
	fileList = (FileDisp*) malloc(sizeof(struct file_display)*(argc-1));
	for(int i = 1; i<argc; i++){
		fileList[i-1] = init_filedisp(argv[i]);
		size++;
	}


	initscr();//Start ncurses
	raw();//Set to raw input mode
	noecho();//Do not print on input
	curs_set(0);//Invisible cursor
	if(has_colors()){//Allow for 'highlighting'
		start_color();
		if(can_change_color()){
			init_pair(1,COLOR_BLACK,COLOR_WHITE);
			init_pair(2,COLOR_WHITE,COLOR_BLACK);
		}
		//bkgd(COLOR_PAIR(2));
		attron(COLOR_PAIR(2));
	}
	keypad(stdscr,true);//Allow detection of more keys
	//Set height and width
	refreshDispSize();
	if(redrawTable()!=0){//First table draw
		clear();
		addstr("Not enough room! Please resize");
	}
	int breakClean=-1;
	while(breakClean==-1){
		int ch = getch();
		switch(ch){
			case KEY_RESIZE:
				refreshDispSize();
				break;
			case ' '://Spacebar
				if(fileList[highlighted]->isSelected){
					fileList[highlighted]->isSelected = 0;
				}
				else{
					fileList[highlighted]->isSelected = 1;
					highlighted++;
					if(highlighted>=size){
						highlighted=0;
					}
				}
				break;
			case 27://Escape
				breakClean=0;
				break;
			case 10://Enter
				breakClean=1;
				break;
			case KEY_UP:
				if(highlighted%height==0){
					highlighted+=height-1;
					if(highlighted>=size)
						highlighted=size-1;
				}
				else{
					highlighted--;
					if(highlighted<0){
						highlighted=size-1;
					}
				}
				break;
			case KEY_DOWN:
				highlighted++;
				if(highlighted%height==0){
					highlighted-=height;
				}
				if(highlighted>=size){
					highlighted-=(highlighted%height);
				}
				break;
			case KEY_LEFT:
				highlighted-=height;
				if(highlighted<0){
					highlighted=0;
				}
				break;
			case KEY_RIGHT:
				highlighted+=height;
				if(highlighted>=size){
					highlighted=size-1;
				}
				break;
		}
		if(redrawTable()!=0){
			clear();
			addstr("Not enough room! Please resize");
		}
	}
	endwin();
	if(breakClean){
		for(int i = 0; i<size; i++){
			if(fileList[i]->isSelected)
				printf("%s ",fileList[i]->filename);
		}
		printf("\n");
	}
}
