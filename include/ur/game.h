#pragma once

#include <iostream>
#include <stdlib.h>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    class Game {
        private:
            bool display;
            Board b;
            players::Player& white_player;
            players::Player& black_player;
            Color turn;

            int get_move(int roll);
            void display_move(int roll, int tile);
            void display_skip(int roll);
            void make_move();
        public:
            Game(players::Player& white, players::Player& black, bool display);
            players::Player& get_player();
            Color play();
    };
}
