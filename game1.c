#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define scr_width 100
#define scr_height 20

char screen[scr_height][scr_width + 1];

int alive = 666;

float time = 0;

int count = 0;

typedef struct
{
	float x;
	float y;
}point;

typedef struct
{
	int j;
	int i;
}location;

typedef struct
{
	point p;
	location loc;
	float speed;
}person;

person man;

void SetLocat()
{
	man.loc.j = round(man.p.x);
	man.loc.i = round(man.p.y);
}

void CellSwap(location a, location b)
{
	char t = screen[a.i][a.j];
	screen[a.i][a.j] = screen[b.i][b.j];
	screen[b.i][b.j] = t;
}

void CalcCoord()
{
	location t = man.loc;
	man.p.y += man.speed += 0.3;
	SetLocat();
	if(man.loc.i != t.i)
		if(man.loc.i > 0 && man.loc.i < scr_height)
			CellSwap(t, man.loc);
		else
			screen[t.i][t.j] = '.';
}

void Initialize()
{
	for(int i = 0; i < scr_height; i++)
		for(int j = 0; j < scr_width; j++)
			screen[i][j] = '.';
	for(int i = 0; i < scr_height; i++)
		screen[i][scr_width] = '\0';
	
	man.loc.i = 1;
	man.loc.j = 10;
	man.p.y = 1;
	man.p.x = 10;
	screen[man.loc.i][man.loc.j] = 'A';
	man.speed = 0;
}

 void Show()
{
	system("cls");
	for(int i = 0; i < scr_width; i++)
		printf("%c", '_');
	printf("\n");
	for(int i = 0; i < scr_height; i++)
		printf("%s\n", screen[i]);
	for(int i = 0; i < scr_width; i++)
		printf("%c", '=');
	printf("\n");
}

void ColSwap(int a, int b)
{
	for(int i = 0; i < scr_height; i++)
	{
		char ta = screen[i][a];
		char tb = screen[i][b];
		if(ta == 'A' || tb == 'A')
		{
			if(i != 0)
				count++;
			if(ta == '|' || ta == '=' || tb == '|' || tb == '=')
			{
				alive = 0;
				count--;
				for(int k = i - 1; k >= 0; k--)
				{
					char t = screen[k][b];
					screen[k][b] = screen[k][a];
					screen[k][a] = t;
				}
				return;
			}
			continue;
		}
		char t = screen[i][b];
		screen[i][b] = screen[i][a];
		screen[i][a] = t;
	} 
}

void GetWall()
{
	int upper = 0, lower = 0;
	while(lower - upper < 7)
	{
		upper = rand() % 20;
		lower = rand() % 20;
	}
	screen[upper][scr_width - 1] = screen[lower][scr_width - 1] = '=';
	for(int i = 0; i < upper; i++)
		screen[i][scr_width - 1] = '|';
	for(int i = lower + 1; i < scr_height; i++)
		screen[i][scr_width - 1] = '|';
}

void WallShift()
{
	for(int i = 0; i < scr_height; i++)
		screen[i][0] = '.';
	
	for(int j = 1; j < scr_width; j++)
		if(screen[0][j] != '.')
			if(alive)
				ColSwap(j - 1, j);
			else
				return;
}

int main()
{
	printf("PRESS UP ARROW TO JUMP\n");
	
	Sleep(2000);
	
	Initialize();
	
	while(man.loc.i >= 0 && man.loc.i < scr_height && alive)
	{
		if(GetKeyState(VK_UP) < 0)
			if(man.speed > 0)
				man.speed = -1;
			else
				man.speed -= 0.7;
		
		if(time > 0.1)
		{
			time = 0;
			GetWall();
		}
		
		CalcCoord();
		
		WallShift();
		
		Show();
		
		printf("\nvert. speed: %.2f\n == %d ==", man.speed, count / 2);
		
		Sleep(10);
		time += 0.01;
	}
	printf("\nGAME OVER");
	Sleep(10000);
	return 0;
}