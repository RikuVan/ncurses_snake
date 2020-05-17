//
// Created by Richard Van Camp on 11.5.2020.
//

#include "player.h"

player::player(ui *console) : console(console) {}

void player::init() {
    int x_max = console->get_x();
    int y_max = console->get_y();

    y_loc = y_max / 2;
    x_loc = x_max / 2;
    alive = true;
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
            else alive = false;
            break;
        case DOWN:
            if (y_loc < y_max - 2) y_loc++;
            else alive = false;
            break;
        case LEFT:
            if (x_loc > 1) x_loc--;
            else alive = false;
            break;
        case RIGHT:
            if (x_loc < x_max - 1) x_loc++;
            else alive = false;
            break;
        default:
            return;
    }

    if (hit_tail(x_loc, y_loc)) alive = false;

    moves.push_front(std::pair(y_loc, x_loc));
}

int player::get_move() {
    const int choice = console->input();
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

struct compare_xy {
    compare_xy(int x, int y) : x(x), y(y) {}

    bool operator()(std::pair<int, int> const &p) {
        // std::cout << p.first << " " << y << " " << p.second << " " <<x;
        return (p.first == y && p.second == x);
    }

private:
    int y;
    int x;
};

bool player::hit_tail(int x, int y) {
    if (moves.size() < 2) return false;
    auto collided = std::find_if(std::next(moves.begin()), moves.end(), compare_xy(x, y));
    return collided != moves.end();
}

bool player::died() {
    return !alive;
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