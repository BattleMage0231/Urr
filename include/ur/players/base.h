#pragma once

#include <ur/board.h>

namespace ur {
    class Player {
        public:
            virtual int get_move(Board& b, int roll) = 0;
    };
}
