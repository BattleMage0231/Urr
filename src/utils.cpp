#include <ur/utils.h>

namespace ur {
    Color opposite(Color t) {
        return (t == Color::WHITE) ? Color::BLACK : Color::WHITE;
    }
}
