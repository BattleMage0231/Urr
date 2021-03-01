#pragma once

namespace ur {
    constexpr int BOARD_SIZE = 14;
    constexpr int NUM_PIECES = 7;

    enum class Color { WHITE, BLACK };

    Color opposite(Color orig);

    struct move {
        bool has_move;
        Color turn;
        int orig, loc;
        bool took_piece;
    };
}
