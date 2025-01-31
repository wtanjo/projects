#include <iostream>
#include <windows.h>
using namespace std;

int screenWidth = 60, screenHeight = 30;
int mapWidth = 35, mapHeight = 25;
wchar_t* screen = new wchar_t[screenWidth * screenHeight];

int main()
{
	for (int i = 0; i < screenWidth * screenHeight; i++)
		screen[i] = L'\u3000';
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
	return 0;
}