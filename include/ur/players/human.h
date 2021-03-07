#pragma once

#include <iostream>
#include <stdexcept>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    /** A human player prompting the user for moves. */
    class HumanPlayer : public virtual Player {
        private:
            /** The color of the current player. */
            Color player_turn;
        public:
            /**
             * The constructor of the HumanPlayer class.
             *
             * @param turn the player's color
             */
            explicit HumanPlayer(Color turn);

            /**
             * Gets the next move the player makes.
             * Should not be called when there are no moves available.
             *
             * @param b a reference of the current game board
             * @param roll the value of the roll
             * @return the possibly invalid tile to move
             * @throws std::invalid_argument if the roll is negative.
             */
            int get_move(Board& b, int roll) override;
    };
}
