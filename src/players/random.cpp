#include <ur/players/random.h>

namespace ur {
    namespace players {
        RandomPlayer::RandomPlayer(Color turn) {}

        int RandomPlayer::get_move(Board b, int roll) {
            return (rand() % (NUM_PIECES + 1)) - 1;
        }
    }
}
