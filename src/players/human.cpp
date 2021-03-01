#include <ur/players/human.h>

namespace ur {
    namespace players {
        human_player::human_player(Color turn) {
            player_turn = turn;
        }

        int human_player::get_move(board b, int roll) {
            using std::cin;
            using std::cout;
            using std::endl;
            cout << ((player_turn == Color::WHITE) ? "White" : "Black") << "'s Turn:" << endl;
            cout << "We have " << b.get_rem(player_turn) << " pieces remaining" << endl;
            cout << "They have " << b.get_rem(opposite(player_turn)) << " pieces remaining" << endl;
            cout << "The roll is a " << roll << endl;
            cout << "Move >>> ";
            int res;
            cin >> res;
            cout << endl;
            return res;
        }
    }
}
