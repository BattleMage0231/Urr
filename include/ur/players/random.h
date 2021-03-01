#pragma once

#include <stdlib.h>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    namespace players {
        class random_player : public virtual player {
            public:
                random_player(Color turn);
                int get_move(board b, int roll);
        };
    }
}
