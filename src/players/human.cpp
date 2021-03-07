#include <ur/players/human.h>

namespace ur {
    HumanPlayer::HumanPlayer(Color turn) : player_turn(turn) {}

    int HumanPlayer::get_move(Board& b, int roll) {
        if(roll < 0) {
            throw std::invalid_argument("Roll value must be non-negative");
        }
        std::string input;
        int res = NULL_POS;
        // prompt the user for their move until it is an integer
        // the board and previous moves are displayed from the Game class
        do {
            std::cout << player_turn << "'s Turn:" << std::endl;
            std::cout << "We have " << b.get_rem(player_turn) << " pieces remaining" << std::endl;
            std::cout << "They have " << b.get_rem(opposite(player_turn)) << " pieces remaining" << std::endl;
            std::cout << "The roll is a " << roll << std::endl;
            std::cout << "Move >>> ";
            std::getline(std::cin, input);
            try {
                // try to parse input as integer
                res = std::stoi(input);
            } catch(std::exception& e) {
                std::cout << std::endl;
                continue;
            }
            std::cout << std::endl;
        } while(std::cin.fail());
        return res;
    }
}
