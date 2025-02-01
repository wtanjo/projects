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

enum Direction
{
	STOP = 0, UP, DOWN, LEFT, RIGHT
};

struct mapNode
{
	int mapX;
	int mapY;
};

bool operator==(mapNode N1, mapNode N2);

class Snake//空格，墙，蛇头，蛇身，果，药，毒，危
{
private:
	wchar_t* private_screen;
	list<mapNode> snake;
	bool GameOver;
	Direction dir;
	mapNode food;
	int score;

public:
	Snake()
	{
		snake = { {mapWidth / 2, mapHeight / 2}, {mapWidth / 2 + 1, mapHeight / 2}, {mapWidth / 2 + 2, mapHeight / 2} };
		GameOver = false;
		dir = STOP;
		score = 0;
		generate_food();
	}

	void get_screen(wchar_t* screen)
	{
		private_screen = screen;
	}

	void generate_food()
	{
		do
		{
			food = { (rand() % (mapWidth - 2) + 1), (rand() % (mapHeight - 2) + 1) };
		} while (find(snake.begin(), snake.end(), food) != snake.end());
	}

	void input_reaction()
	{
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
	}

	void moving_logic()
	{
		if (snake.front().mapX == 0 || snake.front().mapX == mapWidth - 1 || snake.front().mapY == 0 || snake.front().mapY == mapHeight - 1)
			GameOver = true;
		else if (find(++snake.begin(), snake.end(), snake.front()) != snake.end())
			GameOver = true;

		if (snake.front() == food)
		{
			score++;
			generate_food();
		}
		else
			snake.pop_back();
	}

	void write_to_screen_buffer()
	{
		wsprintf(&private_screen[1 * screenWidth + 6], L"按\uff38结束");//全角的X
		wsprintf(&private_screen[2 * screenWidth + 6], L"得分：%-5d", score);//在地图左上方打印，注意一个半角字符也会覆盖一个全角字符造成对齐问题，wsprintf()最后也会自带一个半角空格
		//从{6,3}开始画地图==============================================================================================================================
		for (int x = 0; x < mapWidth; x++)
			for (int y = 0; y < mapHeight; y++)
				private_screen[(y + 3) * screenWidth + (x + 6) + 3] = (x == 0 || x == mapWidth - 1 || y == 0 || y == mapHeight - 1) ? L'墙' : L'\u3000';
		for (int x = 0; x < screenWidth; x++)
			for (int y = 0; y < 2; y++)
				private_screen[(y + mapHeight + 3) * screenWidth + x + 3] = L'\u3000';
		//根据输入、移动及检测填内容进地图
		for (auto sP : snake)
			private_screen[(sP.mapY + 3) * screenWidth + (sP.mapX + 6) + 3] = GameOver ? L'尸' : L'身';//画蛇身
		private_screen[(snake.front().mapY + 3) * screenWidth + (snake.front().mapX + 6) + 3] = GameOver ? L'首' : L'头';//画蛇头(覆盖蛇身第一个元素)
		private_screen[(food.mapY + 3) * screenWidth + (food.mapX + 6) + 3] = L'果';//画食物

		if (GameOver)
		{
			wsprintf(&private_screen[(mapHeight + 3) * screenWidth + 6 + 3], L"按空格键重开");
			wsprintf(&private_screen[(mapHeight + 4) * screenWidth + 6 + 3], L"按\uff45\uff53\uff43键退出");//在地图左下方打印，wsprintf()会覆盖原有内容
		}																						//这里是全角的esc，虽然后面全是空格半角也影响不大，但还是这样用了
	}

	bool game_over()
	{
		return GameOver;
	}
};

class Snake;

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	SetConsoleScreenBufferSize(hConsole, { screenWidth * (short)2, 100 });
	DWORD dwBytesWritten = 0;

	while (1)
	{
		wchar_t* screen = new wchar_t[screenWidth * screenHeight + 3];//显示得分处有6个半角字符，占3个全角字符的面积，为了对齐，字符元素数量要 + 3
		for (int i = 0; i < screenWidth * screenHeight + 3; i++)
			screen[i] = L'\u3000';
		Snake snake;
		snake.get_screen(screen);

		while (!snake.game_over())
		{
			snake.input_reaction();
			snake.moving_logic();
			snake.write_to_screen_buffer();

			WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight + 3, { 0, 0 }, &dwBytesWritten);
			this_thread::sleep_for(200ms);
		}

		while (!_kbhit()) {}
		switch (_getch())
		{
		case 27:
			return 0;
		default:
			break;
		}

		delete[] screen;
	}

	CloseHandle(hConsole);
	return 0;
}


bool operator==(mapNode N1, mapNode N2)
{
	return N1.mapX == N2.mapX && N1.mapY == N2.mapY;
}