#pragma once

#include <ur/board.h>

namespace ur {
    /** An abstract base class representing a player that can make moves. */
    class Player {
        public:
            /**
             * Gets the next move the player makes.
             * Should not be called when there are no moves available.
             *
             * @param b a reference of the current game board
             * @param roll the value of the roll
             * @return the possibly invalid tile to move
             */
            virtual int get_move(Board& b, int roll) = 0;

            /**
             * The destructor of the Player class.
             */
            virtual ~Player() {};
    };
}
