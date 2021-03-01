#pragma once

#include <algorithm>
#include <limits>
#include <utility>
#include <vector>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    namespace players {
        class ai_player : public virtual player {
            private:
                Color player_turn;

                int find_any(bool* pieces, int rem);
                double get_avg(board& b, int depth, Color turn, double alpha, double beta);
                std::pair<double, int> negamax(board& b, int roll, Color turn, int depth, double alpha, double beta);
            public:
                ai_player(Color turn);
                double value_of(board& b, Color turn);
                int get_move(board b, int roll);
        };
    }
}
