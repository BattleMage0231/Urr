#pragma once

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    /** A player that makes its moves based off a negamax algorithm. */
    class AIPlayer : public virtual Player {
        private:
            /** A possible move from a certain board position its associated value. */
            struct Node {

                /** The position to move. */
                int pos;

                /** The value of the move. */
                double value;

                /**
                 * Compares this player with another one based on value.
                 *
                 * @param other the other node
                 * @return whether the current node's value is greater
                 */
                bool operator <(const Node& other) const;
            };

            /** The probability of each possible dice roll. */
            constexpr static double RATES[NUM_DICE + 1] = {0.0625, 0.25, 0.375, 0.25, 0.0625};

            /** The relative value of each board location.  */
            constexpr static double LOC_VALS[BOARD_SIZE] = {
                1.02, 1.30, 1.27, 1.93, 1.28, 1.33, 1.38, 2.38, 1.46, 1.44, 1.38, 1.35, 2.20, 1.75,
            };

            /** The color of the current player. */
            Color player_turn;

            /** The maximum depth the negamax algorithm should search to. */
            unsigned max_depth;

            /**
             * Gets the position of any of pieces that are not yet done.
             * Includes pieces that are off board when they are present.
             * Assumes that there is at least one piece still on the board.
             *
             * @param b the board
             * @param turn which player to search for
             * @return a position that has a piece on it
             * @throws std::logic_error if there are no available pieces.
             */
            static int any_free(const Board& b, Color turn);

            /**
             * Gets the average value at a certain position without knowing the dice roll.
             * Takes into account the probabilities of rolling each number.
             * Calls negamax for each possible roll and takes the weighted average.
             *
             * @param b the board
             * @param depth the current depth of negamax
             * @param turn which player's turn it is
             * @param alpha the current alpha value used in alpha-beta pruning
             * @param beta the current beta value used in alpha-beta pruning
             * @return the average board value
             */
            double get_avg(Board& b, unsigned depth, Color turn, double alpha, double beta) const;

            /**
             * Finds the the best move at a position with optimal play.
             *
             * @param b the board
             * @param depth the current depth
             * @param turn which player's turn it is
             * @param alpha he current alpha value used in alpha-beta pruning 
             * @param beta the current beta value used in alpha-beta pruning
             * @return the best valued node
             */
            Node negamax(Board& b, int roll, Color turn, unsigned depth, double alpha, double beta) const;
        public:
            /**
             * A constructor of the AIPlayer class.
             *
             * @param turn the player's color
             */
            explicit AIPlayer(Color turn);

            /**
             * A constructor of the AIPlayer class taking in a custom depth.
             *
             * @param turn the player's color
             * @param depth the maximum depth to search to
             */
            AIPlayer(Color turn, unsigned depth);

            /**
             * Finds the value of a board for one of the players.
             * Takes into account not only number of pieces but positions of pieces.
             *
             * @param b the board
             * @param turn which player to evaluate
             * @return the value of the board
             */
            static double value_of(const Board& b, Color turn);

            /**
             * Gets the next move the player makes.
             * Should not be called when there are no moves available.
             *
             * @param b the board
             * @param roll the value of the roll
             * @return the tile to move
             * @throws std::invalid_argument if the roll is negative.
             */
            int get_move(Board& b, int roll) override;
    };
}
