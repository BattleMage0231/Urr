#pragma once

#include <random>
#include <stdexcept>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    /** A player that chooses its moves randomly. */
    class RandomPlayer : public virtual Player {
        private:
            /** A uniform distribution to randomly generate tiles. */
            std::uniform_int_distribution<int> tile_dist;
        public:
            /**
             * The constructor of the RandomPlayer class.
             *
             * @param turn the player's color
             */
            explicit RandomPlayer(Color turn);

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
