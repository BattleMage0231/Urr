#include <ur/game.h>

namespace ur {
    Game::Game(players::Player& white, players::Player& black, bool display) 
        : white_player(white)
        , black_player(black)
        , turn(Color::WHITE) 
        , display(display)
    {}

    players::Player& Game::get_player() {
        return (turn == Color::WHITE) ? white_player : black_player;
    }

    int Game::get_move(int roll) {
        Board clone(b);
        return get_player().get_move(clone, roll);
    }

    void Game::display_move(int roll, int tile) {
        std::cout << turn << " played " << tile;
        std::cout << " with roll " << roll << std::endl;
    }

    void Game::display_skip(int roll) {
        std::cout << turn << " had no valid moves for roll " << roll << std::endl;
    }

    void Game::make_move() {
        if(display) b.display_board();
        int roll = 0;
        for(int i = 0; i < NUM_DICE; ++i) {
            roll += rand() % 2;
        }
        if(!b.has_valid(roll, turn)) {
            if(display) display_skip(roll);
            b.no_moves(turn);
            turn = opposite(turn);
            return;
        }
        int tile = get_move(roll);
        while(!b.is_valid(roll, tile, turn)) {
            tile = get_move(roll);
        }
        if(display) display_move(roll, tile);
        b.move_piece(tile, tile + roll, turn);
        if(!is_rosette(tile + roll)) {
            turn = opposite(turn);
        }
    }

    Color Game::play() {
        while(!b.finished()) {
            make_move();
        }
        return b.get_winner();
    }
}
