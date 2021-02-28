#pragma once

#include <iostream>
#include <ur/players/base.h>

namespace ur {
    namespace players {
        class human_player : public virtual player {
            private:
                bool is_white;
            public:
                human_player(bool white);
                int get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll);
        };
    }
}
