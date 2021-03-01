#pragma once

namespace ur {
    namespace players {
        class Player {
            public:
                virtual int get_move(Board b, int roll) = 0;
        };
    }
}
