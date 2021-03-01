#include <ur/utils.h>

namespace ur {
    Color opposite(Color t) {
        return (t == Color::WHITE) ? Color::BLACK : Color::WHITE;
    }

    bool is_competition(int tile) {
        return 4 <= tile && tile <= 11;
    }

    bool is_rosette(int tile) {
        return tile == 3 || tile == 7 || tile == 12;
    }

    bool is_board(int tile) {
        return 0 <= tile && tile <= 13;
    }
}
