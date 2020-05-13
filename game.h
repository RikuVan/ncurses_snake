//
// Created by Richard Van Camp on 12.5.2020.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <unistd.h>
#include "player.h"
#include "ui.h"

class game {
public:
    game(ui *console, std::unique_ptr<player> p);

    void place_fruit();

    void render_fruit();

    void found_fruit();

    void init();

    void loop();

private:
    ui *console;
    std::unique_ptr<player> curr_player;
    int score{0};
    int millis{60 * 2 * 1000};
    std::list<std::pair<int, int>> fruit;

    static constexpr char fruit_char = '@';
};

#endif //SNAKE_GAME_H
