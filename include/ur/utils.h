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

    bool is_competition(int tile);
    bool is_rosette(int tile);
    bool is_board(int tile);
}
