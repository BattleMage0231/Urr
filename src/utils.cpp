#include <ur/utils.h>

namespace ur {
    std::ostream& operator<<(std::ostream& os, const Color& c) {
        return os << (c == Color::WHITE ? "WHITE" : "BLACK");
    };

    Color opposite(Color orig) noexcept {
        return (orig == Color::WHITE) ? Color::BLACK : Color::WHITE;
    }

    std::mt19937 rng;

    void set_seed(unsigned seed) {
        rng.seed(seed);
    }

    bool is_competition(int tile) noexcept {
        return COMP_START <= tile && tile < COMP_END;
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
