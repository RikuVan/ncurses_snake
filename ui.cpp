//
// Created by Richard Van Camp on 13.5.2020.
//

#include "ui.h"

ui::ui() {
    setup();
}

ui::~ui() {
    tear_down();
}

int ui::get_y() {
    return y_max;
};

int ui::get_x() {
    return x_max;
}

void ui::setup() {
    initscr();
    // remove cursor - doesn't always work
    curs_set(0);
    // this allows the program to continue loop after 300 ms wait for input
    // alternatives cbreak, nodelay, timeout
    halfdelay(3);
    // don't print out
    noecho();

    refresh();
    int side = ACS_NEQUAL;
    int top_bottom = ACS_BLOCK;
    int screen_y_max, screen_x_max;
    // get screen dimensions
    // nurses weirdly does everything as y,x
    getmaxyx(stdscr, screen_y_max, screen_x_max);
    // create window in center of screen
    win = newwin(25, 50, (screen_y_max / 2) - 10, 10);
    // get game area maxes
    getmaxyx(win, y_max, x_max);
    // create window border
    wborder(win, side, side, top_bottom, top_bottom, side, side, side, side);
    refresh();
    wrefresh(win);
}

void ui::draw(int x, int y, char c) {
    mvwaddch(win, y, x, c);
}

void ui::erase(int x, int y) {
    mvwaddch(win, y, x, ' ');
}

void ui::draw_bold(int x, int y, char c) {
    wattron(win, A_BOLD);
    mvwaddch(win, y, x, c);
    wattroff(win, A_BOLD);
}

void ui::draw_reversed_colors(int x, int y, char c) {
    wattron(win, A_STANDOUT);
    mvwaddch(win, y, x, c);
    wattroff(win, A_STANDOUT);
}

void ui::redraw() {
    wrefresh(win);
}

int ui::input() {
    int input = getch();
    return input;
}

void ui::tear_down() {
    endwin();
}