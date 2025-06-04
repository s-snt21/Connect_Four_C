# 4 in a Row (Connect Four) – C Language
This is a simple implementation of the classic game **Connect Four** written in C, featuring an animated terminal interface.

## 🎮 How to Play
- Two players take turns dropping colored pieces into a 7x6 grid.
- The first to connect four pieces horizontally, vertically, or diagonally wins.
- If the grid fills up with no winner, the game ends in a draw.

## 🛠️ How to Run the Game
You can run the game in two ways: either run it directly online, or compile and run it via the command line:
#### Method 1: Run Online (Easiest)
Just copy the whole code and paste it in the [OnlineGDB](https://www.onlinegdb.com/) debugger. Then click on the *Run* button. The game will start in the console below.

---

#### Method 2: Compile and Run Locally (Requires Compiler)
**Compilation Requirements**
- A C compiler like GCC, Clang.
- On Windows, it’s recommended to install [MinGW-w64](https://www.mingw-w64.org/) or use [WSL (Windows Subsystem for Linux)](https://learn.microsoft.com/en-us/windows/wsl/install) to get a Linux environment.
- Make sure the compiler is added to your system’s `PATH` environment variable so you can run gcc from any folder.

**Procedure**

Open a terminal and navigate to the folder containing the source file:
```bash
cd path\to\folder
```
Compile the source code:
```bash
gcc 4_in_a_row.c -o 4_in_a_row.exe
```
Run the executable:
```bash
4_in_a_row.exe
```
**Notes**
- Avoid running the game inside IDE consoles like Visual Studio’s built-in terminal, as ANSI color support might be limited and cause display issues.

