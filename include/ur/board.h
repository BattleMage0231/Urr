#pragma once

#include <array>
#include <iostream>
#include <vector>
#include <ur/utils.h>

namespace ur {
    class Board {
        private:
            std::array<bool, BOARD_SIZE> white_pieces;
            std::array<bool, BOARD_SIZE> black_pieces;
            int white_rem = NUM_PIECES;
            int black_rem = NUM_PIECES;
            int white_done = 0;
            int black_done = 0;
            std::vector<Move> moves;
        public:
            Board();
            Board(const Board& orig);
            bool has_piece(int tile, Color turn);
            int get_rem(Color turn);
            int get_done(Color turn);
            bool is_invulnerable(int tile, Color turn);
            bool has_valid(int roll, Color turn);
            bool is_valid(int roll, int tile, Color turn);
            bool finished();
            Color get_winner();
            void display_board();
            void undo_last();
            void no_moves(Color turn);
            void move_piece(int orig, int loc, Color turn);
            ~Board();
    };
}
