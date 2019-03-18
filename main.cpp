#include <bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#define N 25
#define M 50

using namespace std;

struct cell {
	int x, y;
};

int x = 1, y = 1, snakeSize, curentScore;
char marker[N + 23][M + 23], snakeDirection = 'd';
bool fruit, gameover;
cell snake[N * M];

void DrawSnake() {
	for (int i = 1; i <= snakeSize; i++)
		marker[snake[i].x][snake[i].y] = '*';
	if (snakeDirection == 'd')
		marker[snake[1].x][snake[1].y] = '>';
	if (snakeDirection == 'a')
		marker[snake[1].x][snake[1].y] = '<';
	if (snakeDirection == 'w')
		marker[snake[1].x][snake[1].y] = '^';
	if (snakeDirection == 's')
		marker[snake[1].x][snake[1].y] = 'v';		
}

void Init() {
	srand(time(NULL));
	for (int i = 0; i <= M + 1; i++)
		marker[0][i] = marker[N + 1][i] = '!';
	for (int i = 0; i <= N + 1; i++)
		marker[i][0] = marker[i][M + 1] = '!';
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)	
			marker[i][j] = ' ';
	snake[++snakeSize] = {1, 1};
	DrawSnake();
}

void GenFruit() {
	if (fruit == 1)
		return;
	int x = rand() % N + 1;
	int y = rand() % M + 1;
	if (marker[x][y] == ' ') {
		marker[x][y] = 'F';
		fruit = 1;
		return;
	} else GenFruit();
}

void ClearScreen() {
	system("CLS");
}

void AddTail() {
	fruit = 0;
	curentScore++;
	if (snakeSize == 1) {
		++snakeSize;
		snake[2] = snake[1];
		if (snakeDirection == 'a')
			snake[2].y++;
		if (snakeDirection == 'd')
			snake[2].y--;
		if (snakeDirection == 'w')
			snake[2].x++;
		if (snakeDirection == 's')
			snake[2].x--;
		return;
	}
	++snakeSize;
	snake[snakeSize].x = 2 * snake[snakeSize - 1].x - snake[snakeSize - 2].x;
	snake[snakeSize].y = 2 * snake[snakeSize - 1].y - snake[snakeSize - 2].y;
}

void MoveLeft() {
	snakeDirection = 'a';
	cell First = snake[1];
	cell Last = snake[snakeSize];
	for (int i = snakeSize; i > 1; i--)
		snake[i] = snake[i - 1];
	First.y--;
	snake[1] = First;
	marker[Last.x][Last.y] = ' ';
	if (marker[First.x][First.y] != ' ' && marker[First.x][First.y] != 'F')
		gameover = 1;
	if (marker[First.x][First.y] == 'F') 
		AddTail();
}

void MoveRight() {
	snakeDirection = 'd';
	cell First = snake[1];
	cell Last = snake[snakeSize];
	for (int i = snakeSize; i > 1; i--)
		snake[i] = snake[i - 1];
	First.y++;
	snake[1] = First;
	marker[Last.x][Last.y] = ' ';
	if (marker[First.x][First.y] != ' ' && marker[First.x][First.y] != 'F')
		gameover = 1;
	if (marker[First.x][First.y] == 'F') 
		AddTail();
}

void MoveUp() {
	snakeDirection = 'w';
	cell First = snake[1];
	cell Last = snake[snakeSize];
	for (int i = snakeSize; i > 1; i--)
		snake[i] = snake[i - 1];
	First.x--;
	snake[1] = First;
	marker[Last.x][Last.y] = ' ';
	if (marker[First.x][First.y] != ' ' && marker[First.x][First.y] != 'F')
		gameover = 1;
	if (marker[First.x][First.y] == 'F') 
		AddTail();

}

void MoveDown() {
	snakeDirection = 's';
	cell First = snake[1];
	cell Last = snake[snakeSize];
	for (int i = snakeSize; i > 1; i--)
		snake[i] = snake[i - 1];
	First.x++;
	snake[1] = First;
	marker[Last.x][Last.y] = ' ';
	if (marker[First.x][First.y] != ' ' && marker[First.x][First.y] != 'F')
		gameover = 1;
	if (marker[First.x][First.y] == 'F') 
		AddTail();
}

void Exit() {
	cout << "GAME OVER";
}

void Delay(double val) {
	for (double i = 0; i < val; i++) ;
}

void Print() {
	if (snakeDirection == 'a') 
		MoveLeft();
	if (snakeDirection == 'd') 
		MoveRight();
	if (snakeDirection == 'w') 
		MoveUp();
	if (snakeDirection == 's') 
		MoveDown();
	DrawSnake();
	GenFruit();
	if (gameover) {
		Exit();
		return;
	}
	string S = "";
//	cout << "Press W, A, S, D to move\nPress Q to exit the game\n";
//	cout << "Your curent score is : " << curentScore << "\n\n";
//	for (int i = 0; i <= N + 1; i++, putchar('\n'))
//		for (int j = 0; j <= M + 1; j++)
//			putchar(marker[i][j]);
	S += "Press W, A, S, D to move\nPress Q to exit the game\n";
//	S += "Your curent score is : " << curentScore << "\n\n";
	for (int i = 0; i <= N + 1; i++, S += '\n')
		for (int j = 0; j <= M + 1; j++)
			S += marker[i][j];
	cout << S;
	Delay(15000000);
	ClearScreen();
}

int main() {
	Init();
	while (1) {
		while (kbhit()) {
			char c;
			c = getch();
			if (c == 'a' && snakeDirection != 'd')
				MoveLeft();
			if (c == 'd' && snakeDirection != 'a')
				MoveRight();
			if (c == 'w' && snakeDirection != 's')
				MoveUp();
			if (c == 's' && snakeDirection != 'w')
				MoveDown();	
			if (c == 'q')
				return 0;
			Delay(100000);
		}
		Print();
		if (gameover)
			return 0;
	}
	return 0;
}
