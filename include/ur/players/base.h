#pragma once

namespace ur {
    namespace players {
        class player {
            public:
                virtual int get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll) = 0;
        };
    }
}
