//
// Created by Richard Van Camp on 17.5.2020.
//

#ifndef SNAKE_GAME_DB_H
#define SNAKE_GAME_DB_H

#include "sqlite_orm.h"
#include <iostream>

struct snake_game {
    int id;
    int seconds;
    bool died;
    int points;
};

using namespace sqlite_orm;

namespace game_db {
    auto inline create_or_open_db(std::string path_on_disk = "snake.sqlite") {
        return make_storage(path_on_disk,
                            make_table("game",
                                       make_column("id", &snake_game::id, primary_key()),
                                       make_column("seconds", &snake_game::seconds),
                                       make_column("abilities", &snake_game::died),
                                       make_column("points", &snake_game::points)));
    }

    template<typename DB>
    std::tuple<int, int, int, int>  get_all_results(DB db) {
        int played{0}, points{0}, seconds{0}, times_died{0};
        auto games = db.template get_all<snake_game>();
        for (auto &game : games) {
            played++;
            points += game.points;
            seconds += game.seconds;
            if (game.died) times_died++;
        }

        return std::tuple{played, times_died, seconds, points};
    }


    template<typename DB>
    void insert_game_result(DB db, int seconds, bool died, int points) {
        snake_game game{-1, seconds, died, points};
        db.insert(game);
    }

    template<typename DB>
    void remove_all(DB db) {
        db.template remove_all<snake_game>();
    }
}



#endif //SNAKE_GAME_DB_H
