#pragma once

#include <random>
#include <stdexcept>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    class RandomPlayer : public virtual Player {
        private:
            std::uniform_int_distribution<int> tile_dist;
        public:
            explicit RandomPlayer(Color turn);
            int get_move(Board& b, int roll) override;
    };
}
