#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <cmath>
using namespace std;

bool gameOver;
const int width = 30;
const int height = 30;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int foodCounter = 0;
bool superFood = false;
clock_t startTime, superFoodTime;
bool superFoodActive = false;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorPos;

double speedFactor = 1.0;
double baseSpeed = 100;

template<typename T>
double manipulatedSpeedFunction(T x) {
    return baseSpeed - atan(x) * 40;
}

class Direction {
public:
    static const int STOP = 0;
    static const int LEFT = 1;
    static const int RIGHT = 2;
    static const int UP = 3;
    static const int DOWN = 4;
};

int dir;
int highScore = 0;

void SetColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void HideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void ShowCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void ClearScreen() {
    COORD topLeft = {0, 0};
    SetConsoleCursorPosition(hConsole, topLeft);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;
    GetConsoleScreenBufferInfo(hConsole, &screen);
    FillConsoleOutputCharacterA(
        hConsole, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(
        hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(hConsole, topLeft);
}

void Setup() {
    gameOver = false;
    dir = Direction::RIGHT;
    x = width / 2;
    y = height / 2;
    
    // Initialize tail with 3 segments
    nTail = 3;
    tailX[0] = x - 1; tailY[0] = y;
    tailX[1] = x - 2; tailY[1] = y;
    tailX[2] = x - 3; tailY[2] = y;

    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    foodCounter = 0;
    superFood = false;
    superFoodActive = false;
    startTime = clock();
    speedFactor = 1.0;

    HideCursor();
    ClearScreen();
}

void Draw() {
    cursorPos.X = 0;
    cursorPos.Y = 0;
    SetConsoleCursorPosition(hConsole, cursorPos); // Move cursor to the top-left instead of clearing screen

    SetColor(14);
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) { SetColor(14); cout << "#"; }
            if (i == y && j == x) { SetColor(10); cout << "O"; }
            else if (i == fruitY && j == fruitX) { 
                if (superFood) {
                    SetColor(13);
                    cout << "O"; // Large O for superfood
                } else {
                    SetColor(12);
                    cout << "o"; // Small o for normal food
                }
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        SetColor(11);
                        cout << "o";
                        print = true;
                        break;
                    }
                }
                if (!print) {
                    SetColor(8);
                    cout << " ";
                }
            }
            if (j == width - 1) { SetColor(14); cout << "#"; }
        }
        cout << endl;
    }
    SetColor(14);
    for (int i = 0; i < width + 2; i++) cout << "#";
    SetColor(7);
    cout << "\nScore: " << score << "\nTime: " << (clock() - startTime) / CLOCKS_PER_SEC << " sec" << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (dir != Direction::RIGHT) dir = Direction::LEFT; break;
            case 'd': if (dir != Direction::LEFT) dir = Direction::RIGHT; break;
            case 'w': if (dir != Direction::DOWN) dir = Direction::UP; break;
            case 's': if (dir != Direction::UP) dir = Direction::DOWN; break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case Direction::LEFT: x--; break;
        case Direction::RIGHT: x++; break;
        case Direction::UP: y--; break;
        case Direction::DOWN: y++; break;
        default: break;
    }
    if (x >= width || x < 0 || y >= height || y < 0) gameOver = true;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += superFood ? 50 : 10;
        foodCounter++;
        if (foodCounter % 5 == 0) {
            superFood = true;
            superFoodActive = true;
            superFoodTime = clock();
            speedFactor /= 2;
        } else {
            superFood = false;
        }
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }

    if (superFoodActive && (clock() - superFoodTime) / CLOCKS_PER_SEC >= 5) {
        superFoodActive = false;
        speedFactor *= 2;
    }
}

void StartScreen() {
    SetColor(11);
    cout << "******************\n";
    cout << "*   Snake Game   *\n";
    cout << "******************\n";
    SetColor(13);
    cout << "Press 's' to Start\n";
    cout << "Press 'q' to Quit\n";
    char choice = ' ';
    while (choice != 's' && choice != 'q') {
        choice = _getch();
        if (choice == 'q') {
            exit(0);
        }
    }
}

void UpdateHighScore() {
    if (score > highScore) {
        highScore = score;
    }
}

void GameOverScreen() {
    SetColor(12);
    ShowCursor();
    cout << "******************\n";
    cout << "*   Game Over!   *\n";
    cout << "******************\n";
    SetColor(7);
    cout << "Final Score: " << score << endl;
    SetColor(14);
    cout << "High Score: " << highScore << endl;
    SetColor(13);
    cout << "Press 'r' to Restart\n";
    cout << "Press 'q' to Quit\n";
    char choice = ' ';
    while (choice != 'r' && choice != 'q') {
        choice = _getch();
        if (choice == 'q') {
            exit(0);
        } else if (choice == 'r') {
            Setup();
            while (!gameOver) {
                Draw();
                Input();
                Logic();
                Sleep(manipulatedSpeedFunction(nTail) * speedFactor);
            }
            UpdateHighScore();
            GameOverScreen();
        }
    }
}

int main() {
    StartScreen();
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(manipulatedSpeedFunction(nTail) * speedFactor);
    }
    UpdateHighScore();
    GameOverScreen();
    return 0;
}
