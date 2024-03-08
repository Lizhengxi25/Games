#ifndef _Prep_h_
#define _Prep_h_

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

//extern const int MAPHEIGHT = 35;
//extern const int MAPWIDTH = 84;
//extern const int SNAKESIZE = 20;  //蛇的最大节数
//extern const int TEXT_H = MAPHEIGHT / 2 + 1;
//extern const int TEXT_W = MAPWIDTH + 5;

#define MAPHEIGHT 25
#define MAPWIDTH 60
#define SNAKESIZE 15  //蛇的最大节数
#define TEXT_H (MAPHEIGHT / 2)
#define TEXT_W (MAPWIDTH + 5)
#define INIT_V 100

struct FOOD
{
	int x;
	int y;
};
struct FOOD food;

typedef struct SNAKE { //每一节蛇的坐标
	int x[SNAKESIZE + 5];
	int y[SNAKESIZE + 5];
	int len; //蛇长
	int speed; //
	char direction; 
	
//	void (*init_) (struct SNAKE *s);
} SNAKE;
SNAKE snake;

///全局变量
char key = 'w';//初始化移动方向
int changFlag = 0;//蛇变化标记

void gotoxy(int x, int y);

void Write_Len();

void Write_Guide ();

void Write_Begin (); 

void Writing_Result (char success);

#endif
