#pragma once

#include <iostream>
#include <stdlib.h>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    class Game {
        private:
            Board b;
            players::Player& white_player;
            players::Player& black_player;
            Color turn;

            int get_move(int roll);
            void display_move(int roll, int tile);
            void display_no_moves(int roll);
            void move();
        public:
            Game(players::Player& white, players::Player& black);
            players::Player& get_player();
            int start();
    };
}
