#pragma once

#include <stdlib.h>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    namespace players {
        class RandomPlayer : public virtual Player {
            public:
                RandomPlayer(Color turn);
                int get_move(Board b, int roll);
        };
    }
}
