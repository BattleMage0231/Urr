#include <ur/players/random.h>

namespace ur {
    namespace players {
        RandomPlayer::RandomPlayer(Color turn) {}

        int RandomPlayer::get_move(Board& b, int roll) {
            if(roll < 0) {
                throw std::invalid_argument("Roll value must be non-negative");
            }
            return (rand() % (BOARD_SIZE + 1)) - 1;
        }
    }
}
