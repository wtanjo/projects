#define UNICODE
#define _UNICODE

#include <algorithm>
#include <conio.h>
#include <ctime>
#include <iostream>
#include <list>
#include <thread>
#include <windows.h>
using namespace std;

short screenWidth = 60, screenHeight = 30;
short mapWidth = 35, mapHeight = 25;
SMALL_RECT WINDOW = { 0, 0, screenWidth - (short)1, screenHeight - (short)1 };

enum Direction
{
	STOP = 0, UP, DOWN, LEFT, RIGHT
} dir;

struct Node
{
	int mapX;
	int mapY;
};

bool operator==(Node N1, Node N2);

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	wchar_t* screen = new wchar_t[screenWidth * screenHeight];
	for (int i = 0; i < screenWidth * screenHeight; i++)
		screen[i] = L'\u3000';

	SetConsoleScreenBufferSize(hConsole, { screenWidth, screenHeight });
	SetConsoleWindowInfo(hConsole, TRUE, &WINDOW);


	while (1)
	{
		//初始==========================================================================================================================
		//空格，墙，蛇头，蛇身，果，药，毒，危


		//从{6,3}开始画地图
		for (int x = 0; x < mapWidth; x++)
		{
			screen[3 * screenWidth + (x + 6)] = L'墙';
			screen[(mapHeight - 1 + 3) * screenWidth + (x + 6)] = L'墙';
		}
		for (int y = 1; y < mapHeight - 1; y++)
		{
			screen[(y + 3) * screenWidth + 6] = L'墙';
			screen[(y + 3) * screenWidth + (mapWidth - 1 + 6)] = L'墙';
		}
		list<Node> snake = { {mapWidth / 2, mapHeight / 2}, {mapWidth / 2 + 1, mapHeight / 2}, {mapWidth / 2 + 2, mapHeight / 2} };//蛇
		bool GameOver = false;
		dir = STOP;//方向
		int score = 0;//得分
		Node food, poison;
		do
		{
			food = { (rand() % (mapWidth - 2) + 1), (rand() % (mapHeight - 2) + 1) };
		} while (find(snake.begin(), snake.end(), food) != snake.end());//食物

		while (!GameOver)
		{

			//用户输入及蛇的移动==========================================================================================================
			if (_kbhit())
			{
				switch (_getch())
				{
				case 'w':
					dir = UP;
					break;
				case 's':
					dir = DOWN;
					break;
				case 'a':
					dir = LEFT;
					break;
				case 'd':
					dir = RIGHT;
					break;
				case 'x':
					GameOver = true;
					break;
				default:
					break;
				}
			}

			switch (dir)
			{
			case STOP:
				snake.push_back({ snake.back().mapX, snake.back().mapY });
				break;
			case UP:
				snake.push_front({ snake.front().mapX, snake.front().mapY - 1 });
				break;
			case DOWN:
				snake.push_front({ snake.front().mapX, snake.front().mapY + 1 });
				break;
			case LEFT:
				snake.push_front({ snake.front().mapX - 1, snake.front().mapY });
				break;
			case RIGHT:
				snake.push_front({ snake.front().mapX + 1, snake.front().mapY });
				break;
			default:
				break;
			}

			if (snake.front() == food)
			{
				score++;
				do
				{
					food = { (rand() % (mapWidth - 2) + 1), (rand() % (mapHeight - 2) + 1) };
				} while (find(snake.begin(), snake.end(), food) != snake.end());
			}
			else
			{
				snake.pop_back();
			}

			//根据输入、移动及检测填内容进地图============================================================================================
			for (int x = 1; x < mapWidth - 1; x++)
				for (int y = 1; y < mapHeight - 1; y++)
					screen[(y + 3) * screenWidth + (x + 6)] = L'\u3000';
			for (auto sP : snake) 
				screen[(sP.mapY + 3) * screenWidth + (sP.mapX + 6)] = GameOver ? L'尸' : L'身';//画蛇身
			screen[(snake.front().mapY + 3) * screenWidth + (snake.front().mapX + 6)] = GameOver ? L'首' : L'头';//画蛇头(覆盖蛇身第一个元素)
			screen[(food.mapY + 3) * screenWidth + (food.mapX + 6)] = L'果';//画食物



			if (GameOver)
			{
				wsprintf(&screen[(mapHeight + 3) * screenWidth + 6], L"按空格键重开");
				wsprintf(&screen[(mapHeight + 4) * screenWidth + 6], L"按esc键退出");//注意“按空格键重开”的位置是被加入(写入)而不是覆盖
			}

			WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0, 0 }, &dwBytesWritten);

			this_thread::sleep_for(200ms);
		}

		while (!_kbhit()) {}
		switch (_getch())
		{
		case 27:
			return 0;
		case 32:
			break;
		}
	}


	delete[] screen;
	CloseHandle(hConsole);
	return 0;
}

bool operator==(Node N1, Node N2)
{
	return N1.mapX == N2.mapX && N1.mapY == N2.mapY;
}