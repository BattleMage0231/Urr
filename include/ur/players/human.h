#pragma once

#include <iostream>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    namespace players {
        class HumanPlayer : public virtual Player {
            private:
                Color player_turn;
            public:
                HumanPlayer(Color turn);
                int get_move(Board b, int roll);
        };
    }
}
