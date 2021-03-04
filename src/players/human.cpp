#include <ur/players/human.h>

namespace ur {
    namespace players {
        HumanPlayer::HumanPlayer(Color turn) : player_turn(turn) {}

        int HumanPlayer::get_move(Board b, int roll) {
            if(roll < 0) {
                throw std::invalid_argument("Roll value must be non-negative");
            }
            using std::cin;
            using std::cout;
            using std::endl;
            std::string input;
            int res;
            do {
                cout << player_turn << "'s Turn:" << endl;
                cout << "We have " << b.get_rem(player_turn) << " pieces remaining" << endl;
                cout << "They have " << b.get_rem(opposite(player_turn)) << " pieces remaining" << endl;
                cout << "The roll is a " << roll << endl;
                cout << "Move >>> ";
                std::getline(cin, input);
                try {
                    res = std::stoi(input);
                } catch(std::exception& e) {
                    cout << endl;
                    continue;
                }
                cout << endl;
            } while(cin.fail());
            return res;
        }
    }
}
