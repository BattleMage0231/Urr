#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <ur/board.h>

namespace ur {
    class player {
        public:
            virtual int get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll) = 0;
    };

    class human_player : public virtual player {
        private:
            bool is_white;
        public:
            human_player(bool white);
            int get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll);
    };

    class random_player : public virtual player {
        public:
            random_player(bool white);
            int get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll);
    };

    class ai_player : public virtual player {
        private:
            bool is_white;
        public:
            ai_player(bool white);
            double value_of(board& b, bool white_turn);
            double get_avg(board& b, int depth, bool white_turn, double alpha, double beta);
            int find_any(bool* pieces, int rem);
            std::pair<int, double> negamax(board& b, int roll, bool white_turn, int depth, double alpha, double beta);
            int get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll);
    };
}
