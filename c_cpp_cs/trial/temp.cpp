#define UNICODE
#define _UNICODE

#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    int ScreenWidth = 60;
    int ScreenHeight = 30;
    wchar_t *Screen = new wchar_t[ScreenWidth * ScreenHeight];
    for (int i = 0; i < ScreenWidth * ScreenHeight; i++) Screen[i] = L' ';
    Screen[3 * ScreenWidth + 3] = L'X';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;
    WriteConsoleOutputCharacter(hConsole, Screen, ScreenWidth * ScreenHeight, {0, 0}, &dwBytesWritten);
    delete[] Screen;
    Sleep(5000);
    CloseHandle(hConsole);
    return 0;
}