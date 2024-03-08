#ifndef _Writing_h_
#define _Writing_h_

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include "Prep.h"

// ����ƶ� 
void gotoxy(int x, int y) {
	//����win32 APIȥ���ÿ���̨�Ĺ��λ��
	 //1.�ҵ�����̨���������
	 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	 //2.���Ľṹ��
	 COORD coord;
	 //3.���ù��
	 coord.X =x;
	 coord.Y =y;
	 //4.ͬ��������̨  Set Console Cursor Position
	 SetConsoleCursorPosition(handle,coord);
}

void Write_Len() {
	gotoxy(TEXT_W, TEXT_H);
	printf("Length: %d", snake.len);
	gotoxy(0, 0);
	return ;
}

void Snake_init (SNAKE *s) {
	s->len = 3, s->speed = INIT_V;
	memset(s->x, 0, sizeof(s->x));
	memset(s->y, 0, sizeof(s->y));
	s->x[0] = MAPWIDTH / 2, s->y[0] = MAPHEIGHT / 2; //��ʼ��ͷ����Ļ�м�
	return ;
}

void Write_Guide () {
	gotoxy(TEXT_W, TEXT_H / 2 - 1);
	printf("Move:");
	gotoxy(TEXT_W, TEXT_H / 2);
	printf("W: MOVE UP");
	gotoxy(TEXT_W, TEXT_H / 2 + 1);
	printf("A: MOVE LEFT");
	gotoxy(TEXT_W, TEXT_H / 2 + 2);
	printf("S: MOVE DOWN");
	gotoxy(TEXT_W, TEXT_H / 2 + 3);
	printf("D: MOVE RIGHT");
	gotoxy(TEXT_W, TEXT_H - 2);
	printf("Aimed Len: %d", SNAKESIZE);
	return ;
}

void Write_Begin () {
	gotoxy(MAPWIDTH / 2 - 5, MAPHEIGHT / 2);
	printf("Welcom!");
	system("pause");
	gotoxy(MAPWIDTH / 2 - 5, MAPHEIGHT / 2);
	printf("                           ");
}

void Writing_Result (char success) {
	int i = 1; 
	if (!success) {
		for (i = 1; i <= 50; ++i) printf("See you again~\n");
		printf("\n��׹����\n\n");
		printf("Length: %d\n\n\n", snake.len);
	} else {
		for (i = 1; i <= 50; ++i) printf("Man! What can I say?\n");
		printf("\nMAMBA OUT\n\n");
		printf("Length: %d\n\n\n", snake.len);
	}
	return ;
}

#endif
