#include "player.h"
#include "game.h"
#include "ui.h"

void run() {

    ui *console = new ui();
    std::unique_ptr<player> p(new player(console));
    std::unique_ptr<game> g(new game(console, std::move(p)));

    g->loop();

    endwin();
}

int main() {
    run();
    return 0;
}
