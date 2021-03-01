#include <ur/players/random.h>

namespace ur {
    namespace players {
        random_player::random_player(Color turn) {}

        int random_player::get_move(board b, int roll) {
            return (rand() % 15) - 1;
        }
    }
}
