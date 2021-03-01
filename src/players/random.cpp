#include <ur/players/random.h>

namespace ur {
    namespace players {
        random_player::random_player(Color turn) {}

        int random_player::get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll) {
            return (rand() % 15) - 1;
        }
    }
}
