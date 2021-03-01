#pragma once

#include <iostream>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    namespace players {
        class human_player : public virtual player {
            private:
                Color player_turn;
            public:
                human_player(Color turn);
                int get_move(board b, int roll);
        };
    }
}
