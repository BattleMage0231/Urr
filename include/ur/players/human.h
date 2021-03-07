#pragma once

#include <iostream>
#include <stdexcept>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    class HumanPlayer : public virtual Player {
        private:
            Color player_turn;
        public:
            explicit HumanPlayer(Color turn);
            int get_move(Board& b, int roll) override;
    };
}
