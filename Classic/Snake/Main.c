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

//1.����ͼ
void drawMap()
{
    srand((unsigned)time(NULL)); //�����������
    //1.Ȧ��
    //1.1 ���ұ߿�
    int i = 0;
    for(i = 0; i <= MAPHEIGHT; ++i)
    {
        gotoxy(0,i);
        printf("��");
        gotoxy(MAPWIDTH,i);
        printf("��");
    }
    for(i = 0; i <= MAPWIDTH; i += 2) //����  ��ռ�������ַ�
    {
        gotoxy(i, 0);
        printf("��");
        gotoxy(i,MAPHEIGHT);
        printf("��");
    }
    //2.����  ��
    //2.1ȷ���ߵ�����
			//    snake.len = 3;
			//    snake.speed = 100;
			//    snake.x[0] = MAPWIDTH / 2;  //��ʼ��ͷ����Ļ�м�
			//    snake.y[0] = MAPHEIGHT / 2;
	Snake_init (&snake);
    //2.2����ͷ
    gotoxy(snake.x[0], snake.y[0]);
    printf("��"); //һ�� x=2
    //������
	for(i = 1; i <= snake.len - 1; ++i)
	{
	    snake.x[i] = snake.x[i - 1] + 2;
	    snake.y[i] = snake.y[i - 1];
	    gotoxy(snake.x[i], snake.y[i]);
	    printf("��");
	}
    //3.��ʳ��  �� //3.1ȷ������
    food.x = rand() % (MAPWIDTH - 4) + 2;  //�߿�Ŀ����2 ռ�������ַ� ���߱߿����4
    food.y = rand() % (MAPHEIGHT-2) + 1;  //���¸�ռһ��
	if(food.x % 2 != 0) food.x = food.x + 1;
     //3.2 �������Ϳ���
     gotoxy(food.x, food.y);
     printf("��");
}
//2.food
void createFood()
{
	//��ͷ�������ʳ�����꣬���ǳ���
	if(snake.x[0] == food.x && snake.y[0] == food.y)
	{
		srand((unsigned int)time(NULL));
		//������ʳ�ﲻ�����ߵ����ϣ���������Ҫ��ż�� ��Ϊ��ͷ�Ŀ����ż��
		while(1)
		{
			int flag = 1;
			food.x = rand() % (MAPWIDTH - 4) + 2;
			food.y = rand() % (MAPHEIGHT - 2) + 1;
			//������ʳ�ﲻ����������
			int i = 0;
			for (i = 0; i < snake.len; ++i) {
				if (food.x == snake.x[i] && food.y == snake.y[i]) {
					flag = 0;
					break;
				}
			}
			if(flag && food.x % 2 == 0) break;
		}
		gotoxy(food.x, food.y);//�����µ�ʳ��
		printf("��");
		
		snake.len++, snake.speed -= 100 / (INIT_V + 5);
		
		changFlag = 1;//�ߵı����1
	}
	//gotoxy(food.x,food.y);//�����µ�ʳ��
	// printf("��");
	return ;
}
//3.��������
void keyDown() 
{
	//�ް����Ĵ��� ԭ����
	if(_kbhit())
	{//�а���
	    fflush(stdin);
	    key=_getch();
	}
	//����
	if(!changFlag)
	{
	    gotoxy(snake.x[snake.len-1], snake.y[snake.len-1]);
	    printf("  ");//�����ո����β�͡�
	}
	//���������
	int i = 0;
	for(i = snake.len - 1; i > 0; i--)
	{
	    snake.x[i] = snake.x[i - 1];
	    snake.y[i] = snake.y[i - 1];
	}
	//�ƶ�����Ĵ���
	switch(key)
	{
		case 'W': //������ y--
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
		case 'W': //������ y--
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
	
    //����ͷ
    gotoxy(snake.x[0], snake.y[0]);
    printf("��");
    changFlag = 0;
    gotoxy(MAPHEIGHT+2,0); //�ƶ�����һֱ���Ź��
}
//4.�ߵ�״̬���ж��Ƿ������Ϸ
int snakeStatus()
{
	//ײǽ�ж� 
	if (snake.x[0] == 0 || snake.x[0] == MAPWIDTH || snake.y[0] == 0 || snake.y[0] == MAPHEIGHT) return 0;
	//��ͷ����ײ�Լ�
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
		Sleep(snake.speed); //��ʱ
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
