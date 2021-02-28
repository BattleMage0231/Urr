#pragma once

#include <iostream>
#include <stdlib.h>
#include <ur/board.h>
#include <ur/player.h>

namespace ur {
    class game {
        private:
            board b;
            player& white_player;
            player& black_player;
            bool white_turn;
        public:
            game(player& white, player& black);
            player& get_player();
            int get_move(int roll);
            void display_move(int roll, int tile);
            void display_no_moves(int roll);
            void move();
            int start();
    };
}
