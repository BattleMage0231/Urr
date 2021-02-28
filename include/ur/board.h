#pragma once

#include <iostream>
#include <vector>

namespace ur {
    constexpr int BOARD_SIZE = 14;
    constexpr int NUM_PIECES = 7;

    struct move {
        bool has_move;
        bool white_turn;
        int orig, loc;
        bool took_piece;
    };

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
            bool* get_pieces(bool white_turn);
            int get_rem(bool white_turn);
            bool is_competition(int tile);
            bool is_rosette(int tile);
            bool is_board(int tile);
            bool is_vulnerable(int tile, bool white_turn);
            bool has_valid(int roll, bool white_turn);
            bool is_valid(int roll, int tile, bool white_turn);
            int winner();
            void change_rem(int value, bool white_turn);
            void display_board();
            void undo_last();
            void no_moves(bool white_turn);
            void move_piece(int orig, int loc, bool white_turn);
            ~board();
    };
}
