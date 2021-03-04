#pragma once

#include <iostream>
#include <limits>

namespace ur {
    constexpr int BOARD_SIZE = 14;
    constexpr int NUM_PIECES = 7;
    constexpr int NUM_DICE = 4;

    constexpr int NULL_POS = -2;
    constexpr int OFF_BOARD = -1;

    const double INF = std::numeric_limits<double>::max();
    const double NEGINF = -INF;

    enum class Color { WHITE, BLACK };

    std::ostream& operator<<(std::ostream& str, Color const& c);
    Color opposite(Color orig);

    struct Move {
        bool has_move;
        Color turn;
        int orig, loc;
        bool took_piece;
    };

    bool is_competition(int tile);
    bool is_rosette(int tile);
    bool is_board(int tile);
    bool tile_exists(int tile);
}
