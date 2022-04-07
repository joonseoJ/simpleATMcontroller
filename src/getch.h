#if defined(linux) || defined(__APPLE__)
#ifndef CUSTOM_GETCH_H
#define CUSTOM_GETCH_H
#include <termio.h>

int getch(int is_echo){
	int ch; 
	struct termios old; 
	struct termios current; 

	/* Backup current terminal i/o setting*/
	tcgetattr(0, &old); 
	
	/* Copy setting to chance part of it*/
	current = old; 
	
	/* Stop buffer i/o */ 
	current.c_lflag &= ~ICANON; 
	if (is_echo) {
		// If display input
		current.c_lflag |= ECHO; 
	} 
	else { 
		// if not dispay input
		current.c_lflag &= ~ECHO; 
	} 
	/* change setting */ 
	tcsetattr(0, TCSANOW, &current); 
	ch = getchar(); 
	/* unchange setting */
	tcsetattr(0, TCSANOW, &old); 
	
	return ch;
}

#endif
#endif