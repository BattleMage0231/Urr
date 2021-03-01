#pragma once

namespace ur {
    namespace players {
        class player {
            public:
                virtual int get_move(board, int roll) = 0;
        };
    }
}
