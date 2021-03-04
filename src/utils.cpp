#include <ur/utils.h>

namespace ur {
    std::ostream& operator<<(std::ostream& os, Color const& c) {
        return os << (c == Color::WHITE ? "WHITE" : "BLACK");
    };

    Color opposite(Color t) noexcept {
        return (t == Color::WHITE) ? Color::BLACK : Color::WHITE;
    }

    bool is_competition(int tile) noexcept {
        return 4 <= tile && tile <= 11;
    }

    bool is_rosette(int tile) noexcept {
        return tile == 3 || tile == 7 || tile == 12;
    }

    bool is_board(int tile) noexcept {
        return 0 <= tile && tile < BOARD_SIZE;
    }

    bool tile_exists(int tile) noexcept {
        return is_board(tile) || tile == OFF_BOARD;
    }
}
