//
// Created by Richard Van Camp on 11.5.2020.
//

#include "player.h"
#include <iostream>

player::player(ui *console) : console(console) {}

void player::init() {
    int x_max = console->get_x();
    int y_max = console->get_y();

    y_loc = y_max / 2;
    x_loc = x_max / 2;
    moves.clear();
}

void player::move() {
    int x_max = console->get_x();
    int y_max = console->get_y();

    // remove previous head
    console->erase(x_loc, y_loc);

    switch (current_direction) {
        case UP:
            if (y_loc > 1) y_loc--;
            break;
        case DOWN:
            if (y_loc < y_max - 1) y_loc++;
            break;
        case LEFT:
            if (x_loc > 1) x_loc--;
            break;
        case RIGHT:
            if (x_loc < x_max - 1) x_loc++;
            break;
        default:
            break;
    }
    moves.push_front(std::pair(y_loc, x_loc));
}

int player::get_move() {
    int choice = console->input();
    change_direction(choice);
    return choice;
}

std::pair<int, int> player::get_position() {
    return std::pair(y_loc, x_loc);
}

void player::change_direction(int key) {
    if (key == UP || key == DOWN || key == LEFT || key == RIGHT) {
        current_direction = (direction)key;
    }
}

void player::render() {
    // render the tail of the snake from moves list
    std::for_each_n(moves.cbegin(), 6, [=](const std::pair<int, int> spot) {
        if (spot.first > 1 && spot.second > 1) console->draw(spot.second, spot.first, tail_char);
    });
    // remove moves cycled through tail
    if (moves.size() > 6) {
        console->erase(moves.back().second, moves.back().first);
        moves.pop_back();
    }
    // render head of snake
    console->draw_bold(x_loc, y_loc, head_char);
}