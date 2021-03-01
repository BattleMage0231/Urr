#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    namespace players {
        class AIPlayer : public virtual Player {
            private:
                Color player_turn;

                int find_any(bool* pieces, int rem);
                double get_avg(Board& b, int depth, Color turn, double alpha, double beta);
                std::pair<double, int> negamax(Board& b, int roll, Color turn, int depth, double alpha, double beta);
            public:
                AIPlayer(Color turn);
                double value_of(Board& b, Color turn);
                int get_move(Board b, int roll);
        };
    }
}
