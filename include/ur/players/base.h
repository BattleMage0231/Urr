#pragma once

#include <ur/board.h>

namespace ur {
    namespace players {
        class Player {
            public:
                virtual int get_move(Board& b, int roll) = 0;
        };
    }
}
