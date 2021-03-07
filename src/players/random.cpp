#include <ur/players/random.h>

namespace ur {
    RandomPlayer::RandomPlayer(Color turn)
        : tile_dist(std::uniform_int_distribution(OFF_BOARD, BOARD_SIZE - 1))
    {}

    int RandomPlayer::get_move(Board& b, int roll) {
        if(roll < 0) {
            throw std::invalid_argument("Roll value must be non-negative");
        }
        return tile_dist(rng);
    }
}
