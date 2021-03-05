#pragma once

#include <iostream>
#include <limits>
#include <random>

namespace ur {
    constexpr int BOARD_SIZE = 14;
    constexpr int NUM_PIECES = 7;
    constexpr int NUM_DICE = 4;

    constexpr int NULL_POS = -2;
    constexpr int OFF_BOARD = -1;

    const double INF = std::numeric_limits<double>::max();
    const double NEGINF = std::numeric_limits<double>::lowest();

    enum class Color { WHITE, BLACK };

    std::ostream& operator<<(std::ostream& str, const Color& c);
    Color opposite(Color orig) noexcept;

    extern std::mt19937 rng;

    void set_seed(unsigned seed);

    struct Move {
        bool has_move;
        Color turn;
        int orig, loc;
        bool took_piece;
    };

    bool is_competition(int tile) noexcept;
    bool is_rosette(int tile) noexcept;
    bool is_board(int tile) noexcept;
    bool tile_exists(int tile) noexcept;
}
