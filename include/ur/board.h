#pragma once

#include <iostream>
#include <vector>
#include <ur/utils.h>

namespace ur {
    class Board {
        private:
            bool white_pieces[BOARD_SIZE];
            bool black_pieces[BOARD_SIZE];
            int white_rem = NUM_PIECES;
            int black_rem = NUM_PIECES;
            std::vector<Move> moves;
        public:
            Board();
            Board(const Board& orig);
            bool* get_pieces(Color turn);
            int& get_rem(Color turn);
            bool is_vulnerable(int tile, Color turn);
            bool has_valid(int roll, Color turn);
            bool is_valid(int roll, int tile, Color turn);
            int winner();
            void display_board();
            void undo_last();
            void no_moves(Color turn);
            void move_piece(int orig, int loc, Color turn);
            ~Board();
    };
}
