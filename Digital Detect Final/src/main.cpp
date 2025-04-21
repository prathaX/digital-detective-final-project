#include "Game.hpp"899

int main() {
    // Initialize game
    Game game;

    // Game loop
    while (game.running()) {
        // Update
        game.update();

        // Render
        game.render();
    }

    return 0;
}