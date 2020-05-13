//
// Created by Richard Van Camp on 13.5.2020.
//

#ifndef SNAKE_UI_H
#define SNAKE_UI_H

#include <ncurses.h>

class ui {
public:
    ui();

    ~ui();

    void draw(int x, int y, char c);

    void erase(int x, int y);

    void draw_bold(int x, int y, char c);

    void draw_reversed_colors(int x, int y, char c);

    void redraw();

    int input();

    int get_y();

    int get_x();

private:
    int y_max, x_max;
    WINDOW *win;

    void setup();

    void tear_down();
};


#endif //SNAKE_UI_H
