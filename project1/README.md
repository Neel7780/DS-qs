
# Snake Game

A simple Snake game implemented in C++ using the console interface. The game features a moving snake that grows when it eats food, and the player controls the snake using keyboard inputs.

## Features
- **Classic Snake Gameplay**: Move the snake around the board, consuming food and growing in length.
- **Continuous Movement**: The snake moves in real-time, responding instantly to player input.
- **Game Over Conditions**:
  - Collision with the snake's own body.
  - Collision with the game boundary.
- **Score Tracking & Timer**: Displays the player's current score and elapsed time.
- **Super Food Mechanism**:
  - Every 5th food item is a **Super Food**, worth extra points.
  - Temporarily slows down the snake for better control.
  - Lasts for **5 seconds** before returning to normal speed.
- **Dynamic Speed Adjustment**:
  - Snake speed increases as it grows, calculated using **atan(x) scaling**.
  - Ensures gradual difficulty increase without overwhelming the player.
- **Smooth Display**:
  - Console cursor is hidden for a flicker-free experience.
  - Game screen updates dynamically instead of clearing the console.

## How to Play
- Use `W`, `A`, `S`, `D` keys to move Up, Left, Down, and Right, respectively.
- Press `X` to exit the game.
- The goal is to collect food (`o`) and super food (`O`) to grow the snake and increase the score.
- Avoid colliding with the snake's own body to prevent game over.

## Requirements
- A C++ compiler (e.g., g++ or MSVC).
- Windows OS (due to Windows-specific headers like `conio.h` and `windows.h`).

## Compilation and Execution

### Using g++
```sh
 g++ snake_game.cpp -o snake_game.exe
 ./snake_game.exe
```
### Using MSVC
```sh
 cl snake_game.cpp
 snake_game.exe
```

## Code Structure
- **Setup()**: Initializes the game, places the snake and food, and hides the console cursor.
- **Draw()**: Updates the console display with the game state.
- **Input()**: Captures user input for snake movement.
- **Logic()**: Handles movement, food consumption, collision detection, and game over conditions.
- **Main loop**: Continuously calls `Draw()`, `Input()`, and `Logic()` while the game is running.

## Data Structure Analysis
### Arrays
- `tailX[100]`, `tailY[100]`: Used to store the snake's tail coordinates.

### Enum
- `enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };`: Represents the possible movement directions of the snake.

### Variables
- `int x, y`: Stores the snake's head position.
- `int fruitX, fruitY`: Stores the food's position.
- `int score`: Keeps track of the player's score.
- `int nTail`: Stores the current length of the snake's tail.
- `bool gameOver`: Controls the main game loop.
- `clock_t startTime`: Tracks the game duration.

### Speed Variation
The game dynamically adjusts the snake's speed using the **arctangent function** to ensure a smooth and progressive difficulty increase.

#### Formula:
```cpp
 double manipulatedSpeedFunction(int x) {
     return baseSpeed - atan(x) * 40;
 }
```
- The **base speed** is initially set to **100 milliseconds**.
- As the snake length (`nTail`) increases, speed increases gradually.
- The `atan(x)` function prevents extreme speed-ups, maintaining **playability**.

| **Tail Length (`nTail`)** | **Calculated Speed (ms delay)** |
|----------------|----------------------|
| 0  | 100 ms  |
| 5  | 45.2 ms  |
| 10 | 41.2 ms  |
| 20 | 39.2 ms  |

### Super Food Effect
- **Every 5th food** turns into a **Super Food**, marked by a larger symbol (`O`).
- **Effects:**
  1. **Higher Score**: +50 points instead of +10.
  2. **Temporary Speed Reduction**: `speedFactor /= 2;`
  3. **Duration**: Lasts **5 seconds**, after which speed returns to normal.

**Implementation:**
```cpp
if (foodCounter % 5 == 0) {
    superFood = true;
    superFoodActive = true;
    superFoodTime = clock();
    speedFactor /= 2;
}

if (superFoodActive && (clock() - superFoodTime) / CLOCKS_PER_SEC >= 5) {
    superFoodActive = false;
    speedFactor *= 2;
}
```

### Future Improvements
1. **Difficulty Levels**:
   - Implement **Easy, Medium, Hard** modes that affect initial speed and food spawn rate.
   - Example:
     ```cpp
     if (difficulty == "Hard") baseSpeed = 80;
     else if (difficulty == "Medium") baseSpeed = 100;
     else baseSpeed = 120;
     ```

3. **Improved Graphics & UI**:
   - Colored borders, smoother animations, and better fonts.
   - Implement a **main menu** with options to Start, View High Scores, and Quit.

4. **AI Mode**:
   - Implement AI that avoids collisions and seeks food intelligently.

---
This **Snake Game** is designed for an engaging console experience with dynamic speed, score tracking, and special food effects.

## Created By
Team - Code Slayers    

Members:
1) Neel Khatri - 202401093
2) Kavya Bhojwani - 202401090
3) Kavish Inani - 202401089
4) Manal Patel - 202401112  




