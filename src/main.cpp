#include <ur/players.h>
#include <ur/game.h>
#include <ur/utils.h>

#include <ctime>
#include <cstdlib>
#include <exception>
#include <stdlib.h>
#include <unistd.h>

struct Args {
    std::string player1;
    std::string player2;
    unsigned int seed;
    int max_depth;
    bool rand;
    bool verbose;
    int games;
};

void invalid_args(std::string message) {
    std::cerr << message << std::endl;
    exit(1);
}

Args* parse_args(int argc, char* argv[]) {
    int opt;
    Args* args = new Args {
        .player1 = "",
        .player2 = "",
        .seed = (unsigned int) time(nullptr),
        .max_depth = 4,
        .rand = false,
        .verbose = true,
        .games = 1,
    };
    while((opt = getopt(argc, argv, "p:g:s:d:rqvh")) != -1) {
        switch(opt) {
            case 'p': {
                std::string input(optarg);
                if(input == "AI" || input == "HUMAN" || input == "RANDOM") {
                    if(args->player1 == "") {
                        args->player1 = input;
                    } else if(args->player2 == "") {
                        args->player2 = input;
                    } else {
                        invalid_args("The maximum number of players in -p is 2.");
                    }
                } else {
                    invalid_args("Invalid player identifier in -p.");
                }
                break;
            }
            case 'g': {
                std::string input(optarg);
                try {
                    unsigned int games = static_cast<unsigned int>(std::stoul(input));
                    args->games = games;
                } catch(std::exception& e) {
                    invalid_args("Argument to -g must be a positive integer.");
                }
                break;
            }
            case 's': {
                std::string input(optarg);
                try {
                    unsigned int seed = static_cast<unsigned int>(std::stoul(input));
                    args->seed = seed;
                } catch(std::exception& e) {
                    invalid_args("Argument to -s must be a positive integer.");
                }
                break;
            }
            case 'd': {
                std::string input(optarg);
                try {
                    int max_depth = std::stoi(input);
                    if(max_depth < 0) {
                        invalid_args("Argument to -d must be a non-negative integer.");
                    }
                    args->max_depth = max_depth;
                } catch(std::exception& e) {
                    invalid_args("Argument to -d must be a non-negative integer.");
                }
                break;
            }
            case 'r': {
                args->rand = true;
                break;
            }
            case 'q': {
                args->verbose = false;
                break;
            }
            case 'v': {
                std::cout << "Version 1.0" << std::endl;
                exit(0);
            }
            case '?':
            case 'h': {
                std::cout << "Not yet implemented (\"help\")" << std::endl;
                exit(0);
            }
        }
    }
    if(args->player1 == "") {
        args->player1 = "AI";
    }
    if(args->player2 == "") {
        args->player2 = "AI";
    }
    return args;
}

ur::players::Player* from_id(std::string id, ur::Color turn, int max_depth) {
    if(id == "AI") {
        return new ur::players::AIPlayer(turn, max_depth);
    } else if(id == "HUMAN") {
        return new ur::players::HumanPlayer(turn);
    } else if(id == "RANDOM") {
        return new ur::players::RandomPlayer(turn);
    }
    throw;
}

int main(int argc, char* argv[]) {
    using std::cout;
    using std::endl;
    const Args* args = parse_args(argc, argv);
    srand(args->seed);
    int score1 = 0;
    int score2 = 0;
    for(int i = 0; i < args->games; ++i) {
        int p1_color = 0;
        if(args->rand) {
            p1_color = rand() % 2;
        }
        ur::Color color = ur::Color::WHITE;
        if(p1_color == 1) {
            color = ur::Color::BLACK;
        }
        ur::players::Player* white;
        ur::players::Player* black;
        if(color == ur::Color::WHITE) {
            // p1 is white
            white = from_id(args->player1, ur::Color::WHITE, args->max_depth);
            black = from_id(args->player2, ur::Color::BLACK, args->max_depth);
        } else {
            // p1 is black
            white = from_id(args->player2, ur::Color::WHITE, args->max_depth);
            black = from_id(args->player1, ur::Color::BLACK, args->max_depth);
        }
        ur::Game game(*white, *black, args->verbose);
        std::cout << "Started playing game " << i + 1 << std::endl;
        ur::Color winner = game.play();
        delete white;
        delete black;
        if(color == winner) {
            ++score1;
            std::cout << "Player 1 won game " << i + 1 << std::endl; 
        } else {
            ++score2;
            std::cout << "Player 2 won game " << i + 1 << std::endl; 
        }
        std::cout << "Finished game " << i + 1 << " with " << score1 << " : " << score2 << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Player 1's Accuracy: " << (double) score1 / args->games << std::endl;
    std::cout << "Player 2's Accuracy: " << (double) score2 / args->games << std::endl;
    delete args;
    return 0;
}
