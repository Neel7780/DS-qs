#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

const string EMOJI_I = "🟦"; 
const string EMOJI_O = "🟨"; 
const string EMOJI_T = "🟪"; 
const string EMOJI_S = "🟩"; 
const string EMOJI_Z = "🟥"; 
const string EMOJI_J = "🟦"; 
const string EMOJI_L = "🟧"; 

enum class TetrominoType { I, O, T, S, Z, J, L };

class Tetromino {
public:
    TetrominoType type;
    vector<vector<int>> shape;
    int x, y;
    int color;
    string emoji;

    Tetromino(TetrominoType t) : type(t), x(4), y(0) {
        setShape();
        setColor();
        setEmoji();
    }

    void rotate() {
        int n = shape.size();
        vector<vector<int>> rotated(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                rotated[j][n - 1 - i] = shape[i][j];
        shape = rotated;
    }

private:
    void setShape() {
        switch (type) {
            case TetrominoType::I:
                shape = {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};
                break;
            case TetrominoType::O:
                shape = {{1, 1}, {1, 1}};
                break;
            case TetrominoType::T:
                shape = {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}};
                break;
            case TetrominoType::S:
                shape = {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}};
                break;
            case TetrominoType::Z:
                shape = {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}};
                break;
            case TetrominoType::J:
                shape = {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}};
                break;
            case TetrominoType::L:
                shape = {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}};
                break;
        }
    }

    void setColor() {
        switch (type) {
            case TetrominoType::I: color = 11; break; // Cyan
            case TetrominoType::O: color = 14; break; // Yellow
            case TetrominoType::T: color = 13; break; // Magenta
            case TetrominoType::S: color = 10; break; // Green
            case TetrominoType::Z: color = 12; break; // Red
            case TetrominoType::J: color = 9; break; // Blue
            case TetrominoType::L: color = 6; break; // Orange
        }
    }

    void setEmoji() {
        switch (type) {
            case TetrominoType::I: emoji = EMOJI_I; break; // 🟦
            case TetrominoType::O: emoji = EMOJI_O; break; // 🟨
            case TetrominoType::T: emoji = EMOJI_T; break; // 🟪
            case TetrominoType::S: emoji = EMOJI_S; break; // 🟩
            case TetrominoType::Z: emoji = EMOJI_Z; break; // 🟥
            case TetrominoType::J: emoji = EMOJI_J; break; // 🟦
            case TetrominoType::L: emoji = EMOJI_L; break; // 🟧
        }
    }
};

class GameBoard {
public:
    static const int WIDTH = 10, HEIGHT = 20;
    vector<vector<int>> grid;
    vector<vector<string>> emojis;

    GameBoard() : grid(HEIGHT, vector<int>(WIDTH, 0)), emojis(HEIGHT, vector<string>(WIDTH, "")) {}

    void reset() {
        grid = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0));
        emojis = vector<vector<string>>(HEIGHT, vector<string>(WIDTH, ""));
    }

    bool canMove(Tetromino &tet, int dx, int dy) {
        for (size_t i = 0; i < tet.shape.size(); i++) {
            for (size_t j = 0; j < tet.shape[i].size(); j++) {
                if (tet.shape[i][j]) {
                    int newX = tet.x + j + dx;
                    int newY = tet.y + i + dy;
                    if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || (newY >= 0 && grid[newY][newX])) return false;
                }
            }
        }
        return true;
    }

    void placeTetromino(Tetromino &tet) {
        for (size_t i = 0; i < tet.shape.size(); i++) {
            for (size_t j = 0; j < tet.shape[i].size(); j++) {
                if (tet.shape[i][j]) {
                    int boardY = tet.y + i;
                    int boardX = tet.x + j;
                    if (boardY >= 0 && boardY < HEIGHT && boardX >= 0 && boardX < WIDTH) {
                        grid[boardY][boardX] = 1;
                        emojis[boardY][boardX] = tet.emoji;
                    }
                }
            }
        }
    }

    bool isGameOver() {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[0][j]) return true;
        }
        return false;
    }
};

class TetrisGame {
private:
    GameBoard board;
    Tetromino currentPiece;
    Tetromino nextPiece;
    int score;
    int level;
    int linesCleared;
    int speed;
    bool paused;
    int highScore;
    bool gameOver;

public:
    TetrisGame() : currentPiece(randomTetromino()), nextPiece(randomTetromino()), score(0), level(1), linesCleared(0), 
                  speed(100), paused(false), highScore(0), gameOver(false) {}

    Tetromino randomTetromino() {
        return Tetromino(static_cast<TetrominoType>(rand() % 7));
    }

    void clearLines() {
        for (int i = GameBoard::HEIGHT - 1; i >= 0; i--) {
            bool fullLine = true;
            for (int j = 0; j < GameBoard::WIDTH; j++) {
                if (!board.grid[i][j]) {
                    fullLine = false;
                    break;
                }
            }
            if (fullLine) {
                score += 100;
                linesCleared++;
                if (linesCleared % 10 == 0) {
                    level++;
                    if (speed > 10) speed -= 10;
                }
                for (int k = i; k > 0; k--) {
                    for (int j = 0; j < GameBoard::WIDTH; j++) {
                        board.grid[k][j] = board.grid[k - 1][j];
                        board.emojis[k][j] = board.emojis[k - 1][j];
                    }
                }
                for (int j = 0; j < GameBoard::WIDTH; j++) {
                    board.grid[0][j] = 0;
                    board.emojis[0][j] = "";
                }
                i++;
            }
        }
    }

    void togglePause() {
        paused = !paused;
        if (paused) {
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << "--------------------------" << endl;
            cout << "|        ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            cout << "PAUSED";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << "          |" << endl;
            cout << "--------------------------" << endl;
            cout << "Press ESC to resume" << endl;
            cout << "Press R to restart" << endl;
            
            while (paused) {
                if (_kbhit()) {
                    char key = _getch();
                    if (key == 27) {
                        paused = false;
                        break;
                    } else if (key == 'r' || key == 'R') {
                        restartGame();
                        paused = false;
                        break;
                    }
                }
            }
        }
    }

    void restartGame() {
        if (score > highScore) {
            highScore = score;
        }
        
        board.reset();
        score = 0;
        level = 1;
        linesCleared = 0;
        speed = 100;
        gameOver = false;
        
        nextPiece = randomTetromino();
        currentPiece = randomTetromino();
        currentPiece.x = 4;
        currentPiece.y = 0;
        
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "Restarting Game!" << endl;
        Sleep(500);
        
        for (int i = 3; i > 0; i--) {
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << "Game starts in " << i << "..." << endl;
            Beep(400, 300);
            Sleep(500);
        }
        
        system("cls");
    }

    void handleInput() {
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
                case 75: if (board.canMove(currentPiece, -1, 0)) currentPiece.x--; break; // Left arrow
                case 77: if (board.canMove(currentPiece, 1, 0)) currentPiece.x++; break; // Right arrow
                case 80: if (board.canMove(currentPiece, 0, 1)) { currentPiece.y++; score += 1; } break; // Down arrow (soft drop)
                case 72: {
                    auto original = currentPiece.shape;
                    currentPiece.rotate();
                    if (!board.canMove(currentPiece, 0, 0)) {
                        currentPiece.shape = original;
                    }
                    break;
                } // Up arrow (rotate)
                case 32: {
                    int rowsDropped = 0;
                    while (board.canMove(currentPiece, 0, 1)) {
                        currentPiece.y++;
                        rowsDropped++;
                    }
                    score += rowsDropped; // Award 1 point per row for hard drop (same as soft drop)
                    Beep(750, 100);
                    break;
                } // Spacebar (hard drop)
                case 27: togglePause(); break; // ESC (pause)
                case 'r': case 'R': restartGame(); break; // R (restart)
            }
            printGame();
        }
    }

    void gameLoop() {
        startScreen();
        
        while (true) {
            if (gameOver) {
                endScreen();
                
                bool waitingForInput = true;
                while (waitingForInput) {
                    if (_kbhit()) {
                        char key = _getch();
                        if (key == 'r' || key == 'R') {
                            restartGame();
                            waitingForInput = false;
                        } else if (key == 27 || key == 'q' || key == 'Q') {
                            return;
                        }
                    }
                }
            }
            
            handleInput();
            
            if (!paused && !gameOver) {
                if (board.canMove(currentPiece, 0, 1)) {
                    currentPiece.y++;
                } else {
                    Beep(750, 100);
                    board.placeTetromino(currentPiece);
                    clearLines();

                    if (board.isGameOver()) {
                        gameOver = true;
                        continue;
                    }

                    currentPiece = nextPiece;
                    currentPiece.x = 4;
                    currentPiece.y = 0;
                    nextPiece = randomTetromino();
                }

                printGame();
                Sleep(speed);
            }
        }
    }

    void startScreen() {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << "--------------------------" << endl;
        cout << "|        ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        cout << "TETRIS";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << "          |" << endl;
        cout << "--------------------------" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "Press any key to start..." << endl;
        cout << "Controls:" << endl;
        cout << "Arrow Keys - Move and Rotate" << endl;
        cout << "Space - Hard Drop" << endl;
        cout << "ESC - Pause" << endl;
        cout << "R - Restart Game" << endl;
        
        while (!_kbhit()) {}
        _getch();
        
        system("cls");
        const char* frames[] = {
            "   G                  ",
            "   GO                 ",
            "   GO T               ",
            "   GO TE              ",
            "   GO TET             ",
            "   GO TETR            ",
            "   GO TETRI           ",
            "   GO TETRIS          ",
            "   GO TETRIS!         ",
            "   GO TETRIS!!        ",
            "   GO TETRIS!!!       ",
            "  GO TETRIS!!!        ",
            " GO TETRIS!!!         ",
            "GO TETRIS!!!          ",
            " GO TETRIS!!!         ",
            "  GO TETRIS!!!        ",
            "   GO TETRIS!!!       ",
            "    GO TETRIS!!!      ",
            "     GO TETRIS!!!     ",
            "      GO TETRIS!!!    ",
            "       GO TETRIS!!!   ",
            "        GO TETRIS!!!  ",
            "         GO TETRIS!!! ",
            "          GO TETRIS!!!",
            "         GO TETRIS!!! ",
            "        GO TETRIS!!!  ",
            "       GO TETRIS!!!   ",
            "      GO TETRIS!!!    ",
            "     GO TETRIS!!!     ",
            "    GO TETRIS!!!      ",
            "   GO TETRIS!!!       ",
            "  GO TETRIS!!!        ",
            " GO TETRIS!!!         ",
            "GO TETRIS!!!          "
        };
        
        int numFrames = sizeof(frames) / sizeof(frames[0]);
        COORD coord = {0, 0};
        
        for (int i = 0; i < 2; i++) {
            for (int frame = 0; frame < numFrames; frame++) {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                
                if (frame % 3 == 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                } else if (frame % 3 == 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                }
                
                cout << frames[frame] << endl;
                cout << endl;
                cout << "Get ready to play..." << endl;
                
                Beep(300 + (frame % 10) * 50, 50);
                Sleep(50);
            }
        }
        
        Sleep(500);
        system("cls");
    }
    
    void endScreen() {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "--------------------------" << endl;
        cout << "|        ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        cout << "GAME OVER";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "       |" << endl;
        cout << "--------------------------" << endl;
        
        if (score > highScore) {
            highScore = score;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << "New High Score: " << highScore << endl;
        } else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << "Score: " << score << endl;
            cout << "High Score: " << highScore << endl;
        }
        
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << "Press 'R' to restart" << endl;
        cout << "Press 'Q' or 'ESC' to quit" << endl;
    }
    
    void printNextPiece() {
        COORD nextPiecePos = {0, static_cast<SHORT>(GameBoard::HEIGHT + 3)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), nextPiecePos);

    // Clear a larger area to match the 6x6 grid (12 characters wide, 8 rows tall including label and borders)
    for (int i = 0; i < 10; i++) {
        nextPiecePos.Y = static_cast<SHORT>(GameBoard::HEIGHT + 3 + i);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), nextPiecePos);
        cout << string(20, ' '); // Increased to 20 characters to cover the larger frame
    }

    nextPiecePos.Y = static_cast<SHORT>(GameBoard::HEIGHT + 3);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), nextPiecePos);
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "NEXT PIECE:";

    nextPiecePos.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), nextPiecePos);
    cout << "+------------+" << endl; // Border for 6x6 grid (12 characters wide)

    int minX = nextPiece.shape[0].size();
    int minY = nextPiece.shape.size();
    int maxX = 0;
    int maxY = 0;
    
    for (size_t i = 0; i < nextPiece.shape.size(); i++) {
        for (size_t j = 0; j < nextPiece.shape[i].size(); j++) {
            if (nextPiece.shape[i][j]) {
                minX = min(minX, (int)j);
                minY = min(minY, (int)i);
                maxX = max(maxX, (int)j);
                maxY = max(maxY, (int)i);
            }
        }
    }
    
    if (minX > maxX) { minX = 0; maxX = nextPiece.shape[0].size() - 1; }
    if (minY > maxY) { minY = 0; maxY = nextPiece.shape.size() - 1; }

    int pieceWidth = maxX - minX + 1;
    int pieceHeight = maxY - minY + 1;

    // Center the piece perfectly in a 6x6 grid
    int startX = (6 - pieceWidth) / 2; // Center horizontally
    int startY = (6 - pieceHeight) / 2; // Center vertically

    for (int i = 0; i < 6; i++) { // 6 rows for the larger display
        nextPiecePos.Y++;
        nextPiecePos.X = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), nextPiecePos);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "|";

        for (int j = 0; j < 6; j++) { // 6 columns for the larger display
            int pieceI = i - startY + minY;
            int pieceJ = j - startX + minX;

            if (pieceI >= 0 && pieceI < (int)nextPiece.shape.size() &&
                pieceJ >= 0 && pieceJ < (int)nextPiece.shape[0].size() &&
                nextPiece.shape[pieceI][pieceJ]) {
                cout << nextPiece.emoji;
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                cout << ". ";
            }
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "|";
    }

    nextPiecePos.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), nextPiecePos);
    cout << "+------------+" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    
    void printGame() {
        COORD coord = {0, 0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        int sidePanelX = GameBoard::WIDTH * 2 + 10;
        
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "+";
        for (int j = 0; j < GameBoard::WIDTH * 2; j++) {
            cout << "-";
        }
        cout << "+";
        
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << "    TETRIS GAME" << endl;
        
        for (int i = 0; i < GameBoard::HEIGHT; i++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << "|";
            
            for (int j = 0; j < GameBoard::WIDTH; j++) {
                bool isTetromino = false;
                for (size_t ti = 0; ti < currentPiece.shape.size(); ti++) {
                    for (size_t tj = 0; tj < currentPiece.shape[ti].size(); tj++) {
                        if (currentPiece.shape[ti][tj] && i == currentPiece.y + ti && j == currentPiece.x + tj) {
                            isTetromino = true;
                            cout << currentPiece.emoji;
                        }
                    }
                }
                if (isTetromino) {
                    continue;
                } else if (board.grid[i][j]) {
                    cout << board.emojis[i][j];
                } else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    cout << ". ";
                }
            }
            
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << "|";
            
            if (i == 2) {
                COORD statsPos = {static_cast<SHORT>(sidePanelX), static_cast<SHORT>(i)};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), statsPos);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "STATISTICS:";
            } else if (i == 3) {
                COORD scorePos = {static_cast<SHORT>(sidePanelX), static_cast<SHORT>(i)};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), scorePos);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "Score: " << score;
            } else if (i == 4) {
                COORD levelPos = {static_cast<SHORT>(sidePanelX), static_cast<SHORT>(i)};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), levelPos);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "Level: " << level;
            } else if (i == 5) {
                COORD linesPos = {static_cast<SHORT>(sidePanelX), static_cast<SHORT>(i)};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), linesPos);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "Lines: " << linesCleared;
            } else if (i == 6) {
                COORD highScorePos = {static_cast<SHORT>(sidePanelX), static_cast<SHORT>(i)};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), highScorePos);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "High Score: " << highScore;
            } else if (i == 10) {
                COORD controlsPos = {static_cast<SHORT>(sidePanelX), static_cast<SHORT>(i)};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), controlsPos);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                cout << "CONTROLS:";
            } else if (i == 11) {
                COORD movePos = {static_cast<SHORT>(sidePanelX), static_cast<SHORT>(i)};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), movePos);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "Arrow Move";
            } else if (i == 12) {
                COORD rotatePos = {static_cast<SHORT>(sidePanelX), static_cast<SHORT>(i)};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rotatePos);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "Up Rotate";
            } else if (i == 13) {
                COORD dropPos = {static_cast<SHORT>(sidePanelX), static_cast<SHORT>(i)};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), dropPos);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "Space Drop";
            } else if (i == 14) {
                COORD pausePos = {static_cast<SHORT>(sidePanelX), static_cast<SHORT>(i)};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pausePos);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "ESC Pause";
            } else if (i == 15) {
                COORD restartPos = {static_cast<SHORT>(sidePanelX), static_cast<SHORT>(i)};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), restartPos);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "R Restart";
            }
            
            cout << "\n";
        }
        
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "+";
        for (int j = 0; j < GameBoard::WIDTH * 2; j++) {
            cout << "-";
        }
        cout << "+";
        
        printNextPiece();
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    srand(time(0));
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    
    COORD bufferSize = {100, 40}; // Increased height to 40 to accommodate larger "Next Piece" display
    SMALL_RECT windowSize = {0, 0, 99, 39};
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
    
    TetrisGame game;
    game.gameLoop();
    return 0;
}
