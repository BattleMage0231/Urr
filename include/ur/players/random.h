#pragma once

#include <stdlib.h>
#include <ur/players/base.h>

namespace ur {
    namespace players {
        class random_player : public virtual player {
            public:
                random_player(bool white);
                int get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll);
        };
    }
}
