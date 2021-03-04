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
                struct Node {
                    int pos;
                    double value;

                    bool operator <(const Node& other) const;
                };

                int max_depth;
                Color player_turn;

                int any_free(Board& b, Color turn);
                double get_avg(Board& b, int depth, Color turn, double alpha, double beta);
                Node negamax(Board& b, int roll, Color turn, int depth, double alpha, double beta);
            public:
                AIPlayer(Color turn, int max_depth);
                double value_of(Board& b, Color turn);
                int get_move(Board b, int roll);
        };
    }
}
