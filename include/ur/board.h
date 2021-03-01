#pragma once

#include <iostream>
#include <vector>
#include <ur/utils.h>

namespace ur {
    class board {
        private:
            bool white_pieces[BOARD_SIZE];
            bool black_pieces[BOARD_SIZE];
            int white_rem = NUM_PIECES;
            int black_rem = NUM_PIECES;
            std::vector<move> moves;
        public:
            board();
            board(bool* white, int wrem, bool* black, int brem);
            bool* get_pieces(Color turn);
            int get_rem(Color turn);
            bool is_competition(int tile);
            bool is_rosette(int tile);
            bool is_board(int tile);
            bool is_vulnerable(int tile, Color turn);
            bool has_valid(int roll, Color turn);
            bool is_valid(int roll, int tile, Color turn);
            int winner();
            void change_rem(int value, Color turn);
            void display_board();
            void undo_last();
            void no_moves(Color turn);
            void move_piece(int orig, int loc, Color turn);
            ~board();
    };
}
