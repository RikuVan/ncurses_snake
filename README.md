# `Ncurses Snake`

## Playing
This is a simple console snake game made with the Ncurses library. The usual rules apply:
- Eat fruit, which look like this `@`...maybe,  before the timer runs out (60 sec. unless you change it in `game/game.cpp`).
- To navigate, `w` = up `a` = down `s` = right, `z` = down. This was created on a Finnish keyboard, so you may need to adjust these in `player.h`. Ncurses provides some constants for keys as well.
  ```cpp
    enum direction {
        LEFT = 97,
        RIGHT = 115,
        UP = 119,
        DOWN = 122,
        STOP = -1
    };
  ```
  
- You die if you hit an edge of the box or your tail.
- Your cumulative points, play time and deaths are stored in sqlite unless `snake.sqlite` unless another path is provided as an argument to `game_db::create_or_open_db(path)` in main.cpp` 

![Image of snake](images/game.png?raw=true)

## Installation

1. Clone the project repository: `git clone https://github.com/udacity/CppND-System-Monitor-Project-Updated.git`

2. Install dependencies. This game has three dependencies.
- [sqlite](https://www.sqlite.org/index.html): on some operating systems, it is installed by default. Otherwise you will deep to download the executable and install it.
- [sqlite_orm](https://github.com/fnc12/sqlite_orm): the headers are included in the project so you shouldn't need to do anything.
- [ncurses](https://www.gnu.org/software/ncurses/): install Ncurses from source, the repo or using a package manager like `vcpkg` or `conan`. If you are on a mac (as I am), you can use homebrew but you may need to include path in the `MakeLists.txt`. This is already there but commented out.

3. Create a build file, run cmake and make:
```
mkdir build
cd build
run cmake ..run make
```

If all goes well--rarely does--you will have a `build/.snake` executable. Before starting the game from the console, make sure your console has plenty of space.


