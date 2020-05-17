//
// Created by Richard Van Camp on 12.5.2020.
//
#include "game.h"
#include "ui.h"
#include <list>

game::game(ui *console, std::unique_ptr<player> p) noexcept  : console(console), curr_player(std::move(p)) {}

game::game(game &&other) noexcept {
    console = nullptr;
    *console = *other.console;
    curr_player = std::move(other.curr_player);
    score = other.score;
    score = other.millis;
    fruit = other.fruit;
    other.console = nullptr;
    other.score = 0;
    other.millis = 0;
    other.fruit = {};
}

game &game::operator=(game &&other) noexcept {
    if(this != &other) {
        delete console;
        score = 0;
        millis = 0;
        fruit = {};
    }

    return *this;
}

void game::place_fruit() {
    int x_max = console->get_x();
    int y_max = console->get_y();

    auto player_pos = curr_player->get_position();
    int y{player_pos.first};
    int x{player_pos.second};

    while (y == player_pos.first || x == player_pos.second) {
        y = rand() % (y_max * 2 - 2);
        x = rand() % (x_max - 2);
    }

    if (std::find(fruit.begin(), fruit.end(), std::pair(x, y)) == fruit.end()) {
        fruit.push_back(std::pair(x, y));
    }

    auto storage = game_db::create_or_open_db();
    storage.sync_schema();
}

struct compare_xy_pair {
    compare_xy_pair(std::pair<int, int> &p) : y(p.first), x(p.second) {}

    bool operator()(std::pair<int, int> const &p) {
        return (p.first == y && p.second == x);
    }

private:
    int y;
    int x;
};

void game::found_fruit() {
    std::pair<int, int> player_pos = curr_player->get_position();
    auto found = std::find_if(fruit.begin(), fruit.end(), compare_xy_pair(player_pos));

    if (found != fruit.end()) {
        ++score;
        fruit.erase(found);
    }
}

void game::init() {
    curr_player->init();
    fruit.clear();
    score = 0;
    millis = 60 * 1000;
}

void game::render_fruit() {
    for (auto f : fruit) {
        console->draw(f.second, f.first, fruit_char);
    }
}

void game::loop() {
    init();
    console->clear_screen();

    while (millis > 0 && curr_player->get_move() != 27) {
        curr_player->move();
        auto died = curr_player->died();
        if (died) break;
        curr_player->render();
        found_fruit();

        console->print_game_stats(score, millis / 1000);
        console->redraw();

        // add additional fruit after a second, even if others to make it interesting
        if (fruit.empty() || (fruit.size() < 4 && millis % 500 == 0)) {
            place_fruit();
        }

        render_fruit();
        curr_player->render();
        console->redraw();
        // this is the delay for ncurses input
        millis -= 200;
    }

    end_game();
}

int game::get_cmd() {
    const int choice = console->input();

    if (choice == 'c') loop();
    return choice;
}

void game::end_game() {
    auto died = curr_player->died();
    auto x_max = console->get_x();
    auto y_max = console->get_y();

    auto storage = game_db::create_or_open_db();
    // adjust base seconds here if you change the playing time
    int seconds_played = 60 - (millis / 1000);

    game_db::insert_game_result(storage, seconds_played, died, score);
    auto results = game_db::get_all_results(storage);

    const std::string result_msg = died ? "OOPS, YOU DIED." : "GOOD JOB! YOU GOT " + std::to_string(score) + " POINTS.";
    const std::string cmd_msg = "ENTER c TO CONTINUE OR x to EXIT.";
    const std::string stats = "TOTAL: PLAYED "
            + std::to_string(std::get<0>(results))
            + ", DIED " + std::to_string(std::get<1>(results))
            + ", TIME  " + console->format_time(std::get<2>(results))
            + ", POINTS " + std::to_string(std::get<3>(results));

    console->print(x_max / 2 - 4, y_max / 2 - 10, result_msg);
    console->print(x_max / 2 - 4, y_max / 2 - 9, cmd_msg);
    console->print(x_max / 2 - 14, y_max / 2 - 8, stats);

    while(get_cmd() != 'x') {
        usleep(25);
    }
}
