//
// Created by Richard Van Camp on 13.5.2020.
//

#include <string>
#include "ui.h"
#include <string>
#include <iostream>

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
    // hide the crusor - doesn't work on my mmachine
    curs_set(0);
    // cursor is hidden, so leave it wherever
    leaveok(stdscr, TRUE);
    // capture keypad input
    keypad(stdscr, TRUE);
    // move the cursor to the top left
    move(0, 0);;
    // this allows the program to continue loop after 200 ms wait for input
    // alternatives cbreak, nodelay, timeout
    halfdelay(2);
    // don't print out
    noecho();
    keypad(stdscr, TRUE);

    refresh();
    create_screen();
}

void ui::create_screen() {
    int side = '#';
    int top_bottom = '#';
    int screen_y_max, screen_x_max;
    int x_start, y_start;
    // get screen dimensions
    // nurses weirdly does everything as y,x
    getmaxyx(stdscr, screen_y_max, screen_x_max);
    // create window in center of screen
    game_screen = newwin(25, 50, (screen_y_max / 2) - 10, 10);
    score_screen = newwin(5, 50, (screen_y_max / 2) - 15, 10);
    // get game area maxes
    getmaxyx(game_screen, y_max, x_max);
    getmaxyx(score_screen, y_score_max, x_score_max);
    // create window border
    wborder(game_screen, side, side, top_bottom, top_bottom, side, side, side, side);
    wborder(score_screen, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

    refresh();
    wrefresh(game_screen);
    wrefresh(score_screen);
}

void ui::draw(int x, int y, char c) {
    mvwaddch(game_screen, y, x, c);
}

void ui::erase(int x, int y) {
    mvwaddch(game_screen, y, x, ' ');
}

void ui::draw_bold(int x, int y, char c) {
    wattron(game_screen, A_BOLD);
    mvwaddch(game_screen, y, x, c);
    wattroff(game_screen, A_BOLD);
}

void ui::print(int x, int y, const std::string msg) {
    int n = msg.length();
    char chars[n + 1];
    strcpy(chars, msg.c_str());
    mvprintw(y, x, chars);
}

void ui::redraw() {
    wrefresh(game_screen);
    wrefresh(score_screen);
}

int ui::input() {
    int input = getch();
    return input;
}

void ui::clear_screen() {
    clear();
    create_screen();
}

void ui::tear_down() {
    endwin();
}

std::string pad_string(int &num) {
    std::string str = std::to_string(num);
    if(2 > str.size())
        str.insert(0, 2 - str.size(), '0');
    return str;
}

void ui::print_game_stats(int score, int seconds_remaining) {
    int min = seconds_remaining  / 60;
    int sec = seconds_remaining % 60;
    std::string formatted = pad_string(min) + ":" + pad_string(sec);

    print((x_score_max / 2) - 8,  y_score_max + 1, "SCORE: " + std::to_string(score));
    print((x_score_max / 2)  + 6,  y_score_max  + 1, "TIME REMAINING: " +  formatted);
}

std::string ui::format_time(int seconds) {
    int hours = seconds / 3600;
    int min = (seconds % 3699) / 60;
    int sec = seconds % 60;
    return pad_string(hours) + ":" + pad_string(min) + ":" + pad_string(sec);
}