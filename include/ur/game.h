#pragma once

#include <iostream>
#include <random>
#include <ur/utils.h>
#include <ur/board.h>
#include <ur/players/base.h>

namespace ur {
    class Game {
        private:
            Board b;
            Player& white_player;
            Player& black_player;
            Color turn;
            bool display;
            std::uniform_int_distribution<int> dice_dist;

            int get_move(int roll) const;
            void display_move(int roll, int tile) const noexcept;
            void display_skip(int roll) const noexcept;
            void make_move();
        public:
            Game(Player& white, Player& black, bool verbose) noexcept;
            Player& get_player() const noexcept;
            Color play();
    };
}
