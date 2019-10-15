#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

#define LINE 25
#define COLUMN 25
#define SLEEP 100
#define LONG 5

using namespace std;

void HideCursor();//隐藏光标
void Gotoxy(int,int);//坐标
void DetectKey();//检测键盘
void PrintPool();//打印游戏池
void SetColor(int,int);//设置颜色
void Default();//初始化
bool DetectCrash();//检测碰撞
void NewState(bool);//新形态
void RunSnake();//蛇的正常运动
void RandFood();//随机食物


int gamePool[LINE][COLUMN];
int judgePool[LINE][COLUMN];
int headLine;
int headColumn;
int nextLine;
int nextColumn;
int tailNumber;
int direction;// 0 up  1 right  2 down  3 left
int foodNumber;


int main()
{
    srand((unsigned)time(NULL));
    HideCursor();
    Default();
    while(1)
    {
        if(foodNumber <2)
        {
            RandFood();
        }

        if(kbhit())
        {
            DetectKey();
        }

        RunSnake();
        PrintPool();
        Sleep(SLEEP);
    }
    return 0;
}

void Gotoxy(int x,int y)
{
    HANDLE handle;
    COORD pos;
    pos.X = x;
    pos.Y = y;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle,pos);
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void DetectKey()
{
    char control;
    if(kbhit())
    {
        control = getch();
        switch(control)
        {
        case 'w':
        case 'W':
            //gamePool[--headLine][headColumn] = 1;
            direction = 0;
            //NewState(false);
            break;
        case 's':
        case 'S':
            //gamePool[++headLine][headColumn] = 1;
            direction = 2;
            //NewState(false);
            break;
        case 'a':
        case 'A':
            //gamePool[headLine][--headColumn] = 1;
            direction = 3;
            //NewState(false);
            break;
        case 'd':
        case 'D':
           // gamePool[headLine][++headColumn] = 1;
            direction = 1;
            //NewState(false);
            break;
        case ' ':
            getch();
        }
    }
}

void SetColor(int ForeColor = 7,int BackGroundColor = 0)
{
	 HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	 SetConsoleTextAttribute(handle,ForeColor+BackGroundColor*0x10);
}

void PrintPool()
{
    Gotoxy(0,0);
    int i,j;
    for(i=0; i<LINE; i++)
    {
        for(j=0; j<COLUMN; j++)
        {
            if(gamePool[i][j] == 1)
            {
                SetColor(15,0);
                cout << "■";
            }
            else if(gamePool[i][j] > 0)
            {
                SetColor(7,0);
                cout << "■";
            }
            else if(gamePool[i][j] == -2)
            {
                SetColor(9,0);
                cout << "■";
            }
            else if(gamePool[i][j] == -1)
            {
                SetColor(12,0);
                cout << "■";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void Default()
{
    int i,j;
    int t = 1;
    for(i=0; i<LINE; i++)
    {
        for(j=0; j<COLUMN; j++)
        {
            if( i==0 || i==LINE-1 || j==0 || j==COLUMN-1)
            {
                gamePool[i][j] = -1;
                judgePool[i][j] = -1;
            }
            else
            {
                gamePool[i][j] = 0;
                judgePool[i][j] = 0;
            }
        }
    }
    headLine = LINE/2;
    headColumn = COLUMN/2;

    gamePool[headLine][headColumn] = t++;

    for(j=headColumn-1; t!=LONG ; j--)
    {
        gamePool[headLine][j] = t++;
    }

    tailNumber = LONG;
    foodNumber = 0;
    direction = 1;
    nextLine = headLine;
    nextColumn = headColumn+1;
}


void NewState(bool food)
{
    int i,j;
    if(food)
    {
        for(i=0; i<LINE; i++)
        {
            for(j=0; j<COLUMN; j++)
            {
                if(gamePool[i][j] > 0)
                {
                    gamePool[i][j]++;
                }
            }
        }
        tailNumber++;
    }
    else
    {
        for(i=0; i<LINE; i++)
        {
            for(j=0; j<COLUMN; j++)
            {
                if(tailNumber == gamePool[i][j])
                {
                    gamePool[i][j] = 0;
                }
            }
        }
        for(i=0; i<LINE; i++)
        {
            for(j=0; j<COLUMN; j++)
            {
                if(gamePool[i][j] > 0)
                {
                    gamePool[i][j]++;
                }
            }
        }
    }
}

void RunSnake()
{
    switch(direction)
    {
    case 0: nextLine = headLine-1; break;
    case 1: nextColumn = headColumn+1; break;
    case 2: nextLine = headLine+1; break;
    case 3: nextColumn = headColumn-1; break;
    }


    if(gamePool[nextLine][nextColumn] == -2)
    {
        NewState(true);
        headLine = nextLine;
        headColumn = nextColumn;
        gamePool[headLine][headColumn] = 1;
        foodNumber--;
    }
    else if(gamePool[nextLine][nextColumn] != -1)
    {
        NewState(false);
        headLine = nextLine;
        headColumn = nextColumn;
        gamePool[headLine][headColumn] = 1;
    }
    else
    {
        Gotoxy(1,1);
        cout << "你嗝屁了";
        Gotoxy(0,COLUMN);
        exit(0);
    }

}

void RandFood()
{
    int line = rand() % LINE;
    int column = rand() % COLUMN;
    if(gamePool[line][column] != 0)
    {
        RandFood();
    }
    else
    {
        gamePool[line][column] = -2;
        foodNumber ++;
    }
}
