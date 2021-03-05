#pragma once

#include <stdlib.h>
#include <stdexcept>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    namespace players {
        class RandomPlayer : public virtual Player {
            public:
                explicit RandomPlayer(Color turn);
                int get_move(Board& b, int roll) override;
        };
    }
}
