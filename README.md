# Chess

Chess is a terminal-and-X11 chess program that enforces every rule of chess, lets you script games through stdin, and can be played against humans or the bundled computer opponent. The codebase follows a lightweight MVC architecture so the rules engine, controller, text view, and graphical view remain decoupled.

<img width="405" height="428" alt="image" src="https://github.com/user-attachments/assets/5c4a1f40-c3df-4d53-9bca-033264c20f84" />

```
8 rnbqkbnr
7 pppppppp
6  _ _ _ _
5 _ _ _ _ 
4  _ _ _ _
3 _ _ _ _ 
2 PPPPPPPP
1 RNBQKBNR

  abcdefgh
```

## Features

- Validates all moves, including castling, en passant, promotion, and stalemate/checkmate detection.
- Dual displays: an ASCII board in the terminal (`Text` view) and an interactive X11 window that renders PNG piece sprites (`Graphics` view powered by `Xwindow`).
- Flexible setup mode to add/remove pieces or pick the starting side before a game begins.
- Supports human-vs-human or human-vs-AI games; the provided AI implementation is `computer[1]` (random legal move) and higher levels are ready for extension.
- Score tracking and resignation handling across multiple consecutive games.
- Regression tests under `tests/` for scripted scenarios (e.g., `./chess < tests/test13.in`).

## Requirements

- C++20 compiler (Makefile defaults to `g++-11`; edit `CXX` if you need a different compiler).
- `make`
- X11 development headers/libraries (`libX11`).
- libpng development headers/libraries.
- On macOS you also need XQuartz (Homebrew handles this when installing `libx11`).

## Installation

### macOS (Apple Silicon or Intel)

1. Install the Xcode Command Line Tools: `xcode-select --install`.
2. Install Homebrew if you do not already have it: `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`.
3. Install compiler and graphics dependencies:
   ```
   brew install gcc@11 libx11 libpng
   ```
4. Ensure Homebrew’s include/lib paths are accessible; the Makefile already adds `/opt/homebrew/include` and `/opt/homebrew/lib`. If Homebrew lives elsewhere, update `CXXFLAGS`/`LDFLAGS`.

### Linux (Debian/Ubuntu example)

```
sudo apt update
sudo apt install g++ make libx11-dev libpng-dev
```

For other distributions install the equivalent development packages (`libX11-devel`, `libpng-devel`, etc.).

## Build

```
git clone <repo-url>
cd ChessProject
make        # builds ./chess
make clean  # removes objects/binary
```

If you change compilers or need extra include paths, edit the top of `Makefile`.

## Running the Game

Launch the program after building:

```
./chess
```

All interaction happens through stdin/stdout, so you can type commands manually or redirect a script. The core commands are:

- `game <white-player> <black-player>` — starts a new game. Each player is either `human` or `computer[1]`…`computer[4]` (currently only level 1 is implemented; higher levels are hooks for further AI work).
- `move <from> <to>` — performs a move for the current human player using algebraic coordinates (e.g., `move e2 e4`). On an AI turn, just type `move` and the AI will move automatically for you.
- `resign` — concede the current game; scores update immediately.
- `setup` — enter setup mode (see below) before running `game`.
- `Ctrl-D` (EOF) — quits and prints the cumulative score.

After every legal move the board is redrawn in both the console and the graphical window. If a move places the opponent in check or ends the game, the controller prints the status message and either switches turns or resets the board for the next game.

### Setup Mode

`setup` lets you craft arbitrary starting positions before calling `game`. While in setup mode the controller reads one command per line:

- `+ <piece> <coord>` — add a piece. Uppercase letters are white (`P`, `R`, `N`, `B`, `Q`, `K`), lowercase letters are black. Example: `+ K e1`.
- `- <coord>` — remove whatever piece is on that square.
- `= <white|black>` — set which side moves first.
- `done` — exit setup once the board contains exactly one king per side and all pawns are on valid ranks; otherwise you are prompted to continue editing.

You can repeat setup between games to test openings, puzzles, or custom studies.

### Sample Session

```
$ ./chess
game human human
move e2 e4
move e7 e5
move g1 f3
resign
setup
+ K e1
+ k e8
+ Q d1
+ q d8
= white
done
game human computer[1]
move e2 e4
move        # AI responds
```

## Automated Tests

Use the scripted inputs under `tests/` to replay scenarios:

```
./chess < tests/setup1.in
```

These files combine `setup`, `game`, `move`, and `resign` commands to verify rule handling.

Enjoy the game!
