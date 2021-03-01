#pragma once

#include <iostream>
#include <stdlib.h>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    class game {
        private:
            board b;
            players::player& white_player;
            players::player& black_player;
            Color turn;

            int get_move(int roll);
            void display_move(int roll, int tile);
            void display_no_moves(int roll);
            void move();
        public:
            game(players::player& white, players::player& black);
            players::player& get_player();
            int start();
    };
}
