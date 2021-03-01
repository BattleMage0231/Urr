#pragma once

#include <iostream>
#include <ur/utils.h>
#include <ur/players/base.h>

namespace ur {
    namespace players {
        class human_player : public virtual player {
            private:
                Color player_turn;
            public:
                human_player(Color turn);
                int get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll);
        };
    }
}
