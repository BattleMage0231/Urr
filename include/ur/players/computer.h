#pragma once

#include <algorithm>
#include <stdexcept>
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

                unsigned max_depth;
                Color player_turn;

                int any_free(Board& b, Color turn) const;
                double get_avg(Board& b, unsigned depth, Color turn, double alpha, double beta) const;
                Node negamax(Board& b, int roll, Color turn, unsigned depth, double alpha, double beta) const;
            public:
                AIPlayer(Color turn, unsigned max_depth);
                double value_of(Board& b, Color turn) const;
                int get_move(Board b, int roll) override;
        };
    }
}
