#include "game/player.h"
#include "game/game.h"
#include "game/ui.h"

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
