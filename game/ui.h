//
// Created by Richard Van Camp on 13.5.2020.
//

#ifndef SNAKE_UI_H
#define SNAKE_UI_H

#include <ncurses.h>
#include <string>

class ui {
public:
    ui();

    ~ui();

    void draw(int x, int y, char c);

    void erase(int x, int y);

    void draw_bold(int x, int y, char c);

    void print(int x, int y, std::string);

    void redraw();

    void clear_screen();

    void print_game_stats(int score, int seconds_remaining);

    std::string  format_time(int seconds);

    int input();

    int get_y();

    int get_x();

private:
    int y_max, x_max;
    int y_score_max, x_score_max;
    WINDOW *game_screen;
    WINDOW *score_screen;

    void setup();

    void create_screen();

    void tear_down();
};


#endif //SNAKE_UI_H
