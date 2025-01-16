#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

#define WIDTH 50
#define HEIGHT 20

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

void gotoxy(int x, int y);

class Snake {
private:
    vector<pair<int, int>> body;
    Direction dir;
    int score;
    bool gameOver;
    pair<int, int> fruit;

public:
    Snake() {
        dir = STOP;
        score = 0;
        gameOver = false;
        body.push_back(make_pair(WIDTH / 2, HEIGHT / 2));
        generateFruit();
    }

    void generateFruit() {
        do {
            fruit.first = rand() % (WIDTH - 1);
            fruit.second = rand() % (HEIGHT - 1);
        } while (find(body.begin(), body.end(), fruit) != body.end() || (fruit.first == 0 || fruit.second == 0));
    }

    void input() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'a':
                if (body.begin() + 2 == body.end() && dir == RIGHT) {
                    gameOver = true;
                    break;
                }
                dir = LEFT;
                break;
            case 'd':
                if (body.begin() + 2 == body.end() && dir == LEFT) {
                    gameOver = true;
                    break;
                }
                dir = RIGHT;
                break;
            case 'w':
                if (body.begin() + 2 == body.end() && dir == DOWN) {
                    gameOver = true;
                    break;
                }
                dir = UP;
                break;
            case 's':
                if (body.begin() + 2 == body.end() && dir == UP) {
                    gameOver = true;
                    break;
                }
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }
    }

    void logic() {
        pair<int, int> head = body.front();
        switch (dir) {
        case LEFT:
            head.first--;
            break;
        case RIGHT:
            head.first++;
            break;
        case UP:
            head.second--;
            break;
        case DOWN:
            head.second++;
            break;
        default:
            break;
        }

        if (head == fruit) {
            score += 10;
            generateFruit();
        } else {
            body.pop_back();
        }

        if (head.first >= WIDTH - 1 || head.first <= 0 || head.second >= HEIGHT - 1 || head.second <= 0) {
            gameOver = true;
        }

        for (size_t i = 1; i < body.size(); i++) {
            if (head == body[i]) {
                gameOver = true;
                break;
            }
        }

        body.insert(body.begin(), head);
    }

    void map() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (i == 0 || i == HEIGHT - 1)
                    cout << '-';
                else if (j == 0 || j == WIDTH - 1)
                    cout << '|';
                else 
                    cout << ' ';
            }
            cout << endl;
        }
    }

    void content() {
        gotoxy(1, 1);
        for (int i = 1; i < HEIGHT - 1; i++) {
            for (int j = 1; j < WIDTH - 1; j++) {
                cout << ' ';
                if (find(body.begin(), body.end(), make_pair(j, i)) != body.end()) {
                    gotoxy(j, i);
                    cout << 'o';
                }
                else if (make_pair(j, i) == fruit) {
                    gotoxy(j, i);
                    cout << 'F';
                }
            }
            gotoxy(1, i + 1);
        }
        gotoxy(0, HEIGHT);
        cout << "Score: " << score << endl;
    }

    bool isGameOver() {
        return gameOver;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    Snake snake;
    system("cls");
    snake.map();
    while (!snake.isGameOver()) {
        snake.content();
        snake.input();
        snake.logic();
        Sleep(100);
    }
    cout << "Game Over!" << endl;
    Sleep(7000);
    return 0;
}

void gotoxy(int x, int y) {
    COORD pos = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}