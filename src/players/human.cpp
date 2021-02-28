#include <ur/players/human.h>

namespace ur {
    namespace players {
        human_player::human_player(bool white) {
            is_white = white;
        }

        int human_player::get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll) {
            using std::cin;
            using std::cout;
            using std::endl;
            cout << (is_white ? "White" : "Black") << "'s Turn:" << endl;
            cout << "We have " << rem << " pieces remaining" << endl;
            cout << "They have " << opp_rem << " pieces remaining" << endl;
            cout << "The roll is a " << roll << endl;
            cout << "Move >>> ";
            int res;
            cin >> res;
            cout << endl;
            return res;
        }
    }
}
