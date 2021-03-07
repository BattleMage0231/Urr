#include <ur/game.h>

namespace ur {
    Game::Game(Player& white, Player& black, bool verbose) noexcept 
        : white_player(white)
        , black_player(black)
        , turn(Color::WHITE) 
        , display(verbose)
        , dice_dist(std::uniform_int_distribution(0, 1))
    {}

    int Game::get_move(int roll) const {
        Board clone(b);
        return get_player().get_move(clone, roll);
    }

    void Game::display_move(int roll, int tile) const noexcept {
        std::cout << turn << " played " << tile;
        std::cout << " with roll " << roll << std::endl;
    }

    void Game::display_skip(int roll) const noexcept {
        std::cout << turn << " had no valid moves for roll " << roll << std::endl;
    }

    void Game::make_move() {
        if(display) b.display_board();
        int roll = 0;
        for(int i = 0; i < NUM_DICE; ++i) {
            roll += dice_dist(rng);
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

    Player& Game::get_player() const noexcept {
        return (turn == Color::WHITE) ? white_player : black_player;
    }

    Color Game::play() {
        while(!b.finished()) {
            make_move();
        }
        return b.get_winner();
    }
}
