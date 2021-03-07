#pragma once

#include <array>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <ur/utils.h>

namespace ur {
    /** The state of an Ur game, including pieces and the board but not the turn. */
    class Board {
        private:
            /** An array storing the white player's pieces. */
            std::array<bool, BOARD_SIZE> white_pieces;

            /** An array storing the black player's pieces. */
            std::array<bool, BOARD_SIZE> black_pieces;

            /** The number of the white player's pieces still off board. */
            int white_rem;

            /** The number of the black player's pieces still off board. */
            int black_rem;

            /** The number of the white player's pieces that are finished. */
            int white_done;

            /** The number of the black player's pieces that are finished. */
            int black_done;

            /** A list of all of the moves made. */
            std::vector<Move> moves;
        public:
            /**
             * The constructor of the Board class.
             * Initializes a new game of Ur.
             */
            Board() noexcept;

            /**
             * A copy constructor of the Board class.
             * Copies the state of the passed in board.
             *
             * @param orig the board to copy
             */
            Board(const Board& orig) noexcept;

            /**
             * Gets whether a player has a piece at a specific tile. 
             * The tile should be on the board.
             *
             * @param tile the tile
             * @param turn which player to check for
             * @return whether there is a piece at the tile
             */
            bool has_piece(int tile, Color turn) const;

            /**
             * Gets the number of remaining off board pieces of a player.
             *
             * @param turn which player to check for
             * @return the number of remaining pieces.
             */
            int get_rem(Color turn) const noexcept;

            /**
             * Gets the number of finished pieces of a player.
             *
             * @param turn which player to check for
             * @return the number of finished pieces.
             */
            int get_done(Color turn) const noexcept;

            /**
             * Gets whether a player's piece is invulnerable.
             * A piece is invulnerable on a rosette tile that is in the competition zone.
             * Returns false if the player has no tile at that position.
             *
             * @param tile the tile
             * @param turn which player to check for
             * @return whether the player has an invulnerable piece on that tile
             */
            bool is_invulnerable(int tile, Color turn) const;

            /**
             * Gets whether a player has a valid move at a position.
             * Players without a valid move are forced to skip their turn.
             *
             * @param roll the roll of the dice
             * @param turn which player to check for
             * @return whether the player has a valid move
             * @throws std::invalid_argument if the roll value is negative.
             */
            bool has_valid(int roll, Color turn) const;

            /**
             * Gets whether a move is valid for a player.
             * The following is an exhaustive list of valid types of moves.
             * 1. An off board piece is moved to a tile without a same colored piece.
             * 2. A piece is moved from a position to a new position on the board
             * without a same colored piece and does not contain an invulnerable opponent piece.
             * 3. A piece is moved from a position to exactly off board, making it finished.
             *
             * @param roll the roll of the dice
             * @param tile the move
             * @param turn which player to check for
             * @return whether the move is valid
             * @throws std::invalid_argument if the roll value is negative.
             */
            bool is_valid(int roll, int tile, Color turn) const;

            /**
             * Gets whether the game is finished (either player has won).
             *
             * @return whether the game is finished.
             */
            bool finished() const noexcept;

            /**
             * Gets the winner of the game, assuming the game is finished.
             *
             * @return the winning side
             * @throws std::logic_error if the game is ongoing.
             */
            Color get_winner() const;

            /**
             * Displays the current board.
             */
            void display_board() const noexcept;

            /**
             * Undos the last move made according to the internal list.
             * Assumes at least one move has been made.
             */
            void undo_last();

            /**
             * Appends a null move to the internal list, signifying that a player
             * did not have any valid moves at a position.
             *
             * @param turn the player
             */
            void no_moves(Color turn);

            /**
             * Moves a player's piece from an original tile to a new tile.
             * Possibly captures an opponent piece.
             *
             * @param orig the original location (can be off board)
             * @param loc the new location (can be finished)
             * @param turn the player
             */
            void move_piece(int orig, int loc, Color turn);
    };
}
