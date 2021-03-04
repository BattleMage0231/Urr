#pragma once

#include <array>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <ur/utils.h>

namespace ur {
    class Board {
        private:
            std::array<bool, BOARD_SIZE> white_pieces;
            std::array<bool, BOARD_SIZE> black_pieces;
            int white_rem;
            int black_rem;
            int white_done;
            int black_done;
            std::vector<Move> moves;
        public:
            Board() noexcept;
            Board(const Board& orig) noexcept;
            bool has_piece(int tile, Color turn) const;
            int get_rem(Color turn) const noexcept;
            int get_done(Color turn) const noexcept;
            bool is_invulnerable(int tile, Color turn) const;
            bool has_valid(int roll, Color turn) const;
            bool is_valid(int roll, int tile, Color turn) const;
            bool finished() const noexcept;
            Color get_winner() const;
            void display_board() const noexcept;
            void undo_last();
            void no_moves(Color turn);
            void move_piece(int orig, int loc, Color turn);
    };
}
