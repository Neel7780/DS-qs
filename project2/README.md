# Tetris_Game
Here, we have uploaded our tetris game we created for our DS-OOPs course.
A classic Tetris game implementation in C++ that runs in the Windows console with colored tetrominoes and sound effects.

## Features

- Classic Tetris gameplay with 7 standard tetromino shapes (I, O, T, S, Z, J, L)
- Emoji-based tetromino blocks (🟦, 🟨, 🟪, 🟩, 🟥, 🟧)
- Color-coded pieces using console text attributes
- Sound effects for piece placement and level transitions
- Comprehensive scoring system with level progression
- Line clearing with points system
- Next piece preview display
- Pause functionality with menu
- High score tracking during session
- Animated start and game over screens
- Responsive controls with keyboard input
- Game statistics display (score, level, lines cleared)

## Controls

- Left Arrow (←): Move piece left
- Right Arrow (→): Move piece right
- Down Arrow (↓): Soft drop (faster falling)
- Up Arrow (↑): Rotate piece
- Spacebar: Hard drop (instant fall)
- ESC: Toggle pause
- R: Restart game

## Gameplay

- Pieces fall automatically at increasing speeds based on level
- Score increases with each soft drop (1 point) and line clear (100 points)
- Level increases every 10 lines cleared
- Game speed increases with each level
- Game ends when pieces stack to the top
- Next piece is displayed for strategic planning

## Requirements

- Windows operating system (uses Windows.h for console manipulation)
- C++ compiler supporting C++11 or later
- UTF-8 support for emoji display
- Standard C++ libraries

## Installation

1. Clone or download the repository
2. Compile the source code using a C++ compiler:

```
g++ tetris.cpp -o tetris
```

1. Run the executable:

```
tetris.exe
```

## Building

The game uses:

- `<iostream>` for console I/O
- `<vector>` for game board and piece representation
- `<conio.h>` for keyboard input
- `<windows.h>` for console manipulation and sound
- `<ctime>` for random piece generation

## How to Play

1. Run the executable
2. Press any key at the start screen to begin
3. Use arrow keys to move and rotate pieces
4. Spacebar for instant drops
5. ESC to pause/resume
6. Clear lines to score points
7. Game ends when pieces reach the top
8. Use the next piece preview to plan your moves
9. Press R to restart or ESC/Q to quit when game is over

## Scoring

- Soft drop: 1 point per block
- Hard drop: 1 point per row moved down
- Line clear: 100 points per line
- Level up: Every 10 lines cleared
- Speed increases with each level

## Technical Details

- Console window is automatically sized to fit the game
- UTF-8 encoding for displaying emoji blocks
- Custom rendering engine for smooth gameplay
- Game state management for pause, restart, and game over conditions

## Known Issues

- Console window must support UTF-8 for proper emoji display
- Colors may display differently depending on console settings
- Sound requires Windows sound capabilities

## Future Improvements

- Add hold piece functionality
- Implement different game modes (Marathon, Sprint, Ultra)
- Include background music
- Add difficulty selection
- Improve game over animation

## Created By

**Team Name** - Code Slayers

**Team Members**

1. Neel Khatri - 202401093
2. Kavya Bhojwani - 202401090
3. Kavish Inani - 202401089
4. Manal Patel - 202401112
