#ifndef CUSTOM_GETCH_H
#define CUSTOM_GETCH_H
#include <termio.h>

int getch(int is_echo){
	int ch; 
	struct termios old; 
	struct termios current; 

	/* 현재 설정된 terminal i/o 값을 backup함 */ 
	tcgetattr(0, &old); 
	
	/* 현재의 설정된 terminal i/o에 일부 속성만 변경하기 위해 복사함 */
	current = old; 
	
	/* buffer i/o를 중단함 */ 
	current.c_lflag &= ~ICANON; 
	if (is_echo) {
		// 입력값을 화면에 표시할 경우 
		current.c_lflag |= ECHO; 
	} 
	else { 
		// 입력값을 화면에 표시하지 않을 경우 
		current.c_lflag &= ~ECHO; 
	} 
	/* 변경된 설정값으로 설정합니다.*/ 
	tcsetattr(0, TCSANOW, &current); 
	ch = getchar(); 
	tcsetattr(0, TCSANOW, &old); 
	
	return ch;
}

#endif