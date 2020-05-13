#ifndef SNAKE_PLAYER_H
#define SNAKE_PLAYER_H

#include <utility>
#include <list>
#include "ui.h"

enum direction {
    LEFT = 97,
    RIGHT = 115,
    UP = 119,
    DOWN = 122,
    STOP = -1
};

class player {
public:
    player(ui *console);

    void init();

    void move();

    void change_direction(int key);

    int get_move();

    void render();

    std::pair<int, int> get_position();

private:
    int y_loc, x_loc;
    std::list<std::pair<int, int>> moves;
    direction current_direction = STOP;
    ui *console;

    static constexpr char head_char = '0';
    static constexpr char tail_char = '.';
};

#endif //SNAKE_PLAYER_H