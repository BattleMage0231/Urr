#pragma once

#include <iostream>
#include <random>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    /** A game of Ur, with a board and players. */
    class Game {
        private:
            /** The board of the game. */
            Board b;

            /** The white player. */
            Player& white_player;

            /** The black player. */
            Player& black_player;

            /** The current turn. */
            Color turn;

            /** Whether moves and the board should be displayed. */
            bool display;

            /** A uniform distribution for one dice (0 or 1). */
            std::uniform_int_distribution<int> dice_dist;

            /**
             * Gets the next move from one of the players.
             * Gives the players a clone of the board.
             *
             * @param roll the roll
             * @return the possibly invalid move
             */
            int get_move(int roll) const;

            /**
             * Displays a message describing a move.
             *
             * @param roll the roll
             * @param tile the move
             */
            void display_move(int roll, int tile) const noexcept;

            /**
             * Displays a message describing that a player has no valid moves.
             *
             * @param roll the roll
             */
            void display_skip(int roll) const noexcept;

            /**
             * Simulates the next move.
             */
            void make_move();
        public:
            /**
             * The constructor of the Game class.
             *
             * @param white the white player
             * @param black the black player
             * @param verbose whether to display messages
             */
            Game(Player& white, Player& black, bool verbose) noexcept;

            /**
             * Gets a reference to the current player.
             *
             * @return the current player
             */
            Player& get_player() const noexcept;

            /**
             * Starts playing the game, assuming it hasn't been played.
             * 
             * @return the winning player
             */
            Color play();
    };
}
