#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "Prep.h"
#include "Writing.h"

void drawMap();
void createFood();
int snakeStatus();

//1.画地图
void drawMap()
{
    srand((unsigned)time(NULL)); //随机函数种子
    //1.圈地
    //1.1 左右边框
    int i = 0;
    for(i = 0; i <= MAPHEIGHT; ++i)
    {
        gotoxy(0,i);
        printf("■");
        gotoxy(MAPWIDTH,i);
        printf("■");
    }
    for(i = 0; i <= MAPWIDTH; i += 2) //上下  ■占用两个字符
    {
        gotoxy(i, 0);
        printf("■");
        gotoxy(i,MAPHEIGHT);
        printf("■");
    }
    //2.画蛇  ■
    //2.1确定蛇的属性
			//    snake.len = 3;
			//    snake.speed = 100;
			//    snake.x[0] = MAPWIDTH / 2;  //开始蛇头放屏幕中间
			//    snake.y[0] = MAPHEIGHT / 2;
	Snake_init (&snake);
    //2.2画蛇头
    gotoxy(snake.x[0], snake.y[0]);
    printf("■"); //一节 x=2
    //画身体
	for(i = 1; i <= snake.len - 1; ++i)
	{
	    snake.x[i] = snake.x[i - 1] + 2;
	    snake.y[i] = snake.y[i - 1];
	    gotoxy(snake.x[i], snake.y[i]);
	    printf("■");
	}
    //3.画食物  ● //3.1确定坐标
    food.x = rand() % (MAPWIDTH - 4) + 2;  //边框的宽度是2 占用两个字符 两边边框就是4
    food.y = rand() % (MAPHEIGHT-2) + 1;  //上下各占一个
	if(food.x % 2 != 0) food.x = food.x + 1;
     //3.2 画出来就可以
     gotoxy(food.x, food.y);
     printf("●");
}
//2.food
void createFood()
{
	//蛇头坐标等于食物坐标，就是吃了
	if(snake.x[0] == food.x && snake.y[0] == food.y)
	{
		srand((unsigned int)time(NULL));
		//产生的食物不能在蛇的身上，并且坐标要是偶数 因为蛇头的宽度是偶数
		while(1)
		{
			int flag = 1;
			food.x = rand() % (MAPWIDTH - 4) + 2;
			food.y = rand() % (MAPHEIGHT - 2) + 1;
			//产生的食物不能在蛇身上
			int i = 0;
			for (i = 0; i < snake.len; ++i) {
				if (food.x == snake.x[i] && food.y == snake.y[i]) {
					flag = 0;
					break;
				}
			}
			if(flag && food.x % 2 == 0) break;
		}
		gotoxy(food.x, food.y);//产生新的食物
		printf("●");
		
		snake.len++, snake.speed -= 100 / (INIT_V + 5);
		
		changFlag = 1;//蛇的标记是1
	}
	//gotoxy(food.x,food.y);//产生新的食物
	// printf("●");
	return ;
}
//3.按键操作
void keyDown() 
{
	//无按键的处理 原方向
	if(_kbhit())
	{//有按键
	    fflush(stdin);
	    key=_getch();
	}
	//擦除
	if(!changFlag)
	{
	    gotoxy(snake.x[snake.len-1], snake.y[snake.len-1]);
	    printf("  ");//两个空格擦掉尾巴。
	}
	//后面的蛇身
	int i = 0;
	for(i = snake.len - 1; i > 0; i--)
	{
	    snake.x[i] = snake.x[i - 1];
	    snake.y[i] = snake.y[i - 1];
	}
	//移动方向的处理
	switch(key)
	{
		case 'W': //往上走 y--
		case 'w':
			if (snake.direction != 's' && snake.direction != 'S') snake.direction = key;
			break;
		case 'S':
		case 's':
			if (snake.direction != 'w' && snake.direction != 'W') snake.direction = key;
			break;
		case 'A':
		case 'a':
			if (snake.direction != 'd' && snake.direction != 'D') snake.direction = key;
			break;
		case 'd':
		case 'D':
			if (snake.direction != 'a' && snake.direction != 'A') snake.direction = key;
			break;
		default : break;
	}
	switch(snake.direction)
	{
		case 'W': //往上走 y--
		case 'w':
			snake.y[0]--;
			break;
		case 'S':
		case 's':
			snake.y[0]++;
			break;
		case 'A':
		case 'a':
			snake.x[0] -= 2;
			break;
		case 'd':
		case 'D':
			snake.x[0] += 2;
			break;
	}
	
    //画蛇头
    gotoxy(snake.x[0], snake.y[0]);
    printf("■");
    changFlag = 0;
    gotoxy(MAPHEIGHT+2,0); //移动不能一直看着光标
}
//4.蛇的状态：判断是否结束游戏
int snakeStatus()
{
	//撞墙判定 
	if (snake.x[0] == 0 || snake.x[0] == MAPWIDTH || snake.y[0] == 0 || snake.y[0] == MAPHEIGHT) return 0;
	//蛇头不能撞自己
	int i = 1;
	for(i = 1; i <= snake.len - 1; i++)
	{
		if(snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i]) return 0;
	}
	return 1;
}

int main(){
	char success = 0;
	
	Write_Guide();
	Write_Begin();
	drawMap();
	while(snakeStatus() && !success)
	{
		createFood();
		Sleep(snake.speed); //延时
		keyDown();
		Write_Len();
//		if (snake.len == SNAKESIZE / 2 && snake.speed != 80) snake.speed = 80;
		if (snake.len == SNAKESIZE) success = 1;
	}
	Sleep(500); 
	gotoxy(0, MAPHEIGHT + 1);
	Writing_Result(success);
	system("pause"); //
  return 0;
}
