#include <ur/players/computer.h>
#include <ur/players/human.h>
#include <ur/players/random.h>
#include <ur/game.h>
#include <ur/utils.h>

#include <ctime>
#include <cstdlib>
#include <exception>
#include <memory>
#include <unistd.h>

// conveniently print an error message and exit the program
void err(const std::string& msg) {
    std::cerr << msg << std::endl;
    exit(1);
}

struct Args {
    std::string player1;    // the type of the first player ("AI", "HUMAN", "RANDOM")
    std::string player2;    // the type of the second player
    unsigned seed;          // the seed of the random number generator
    unsigned max_depth;     // the maximum depth of the AI player
    bool rand;              // whether the colors should be randomized
    bool verbose;           // whether to display moves and the board
    unsigned games;         // the number of games to play
};

// parses the command line arguments into a struct
std::unique_ptr<Args> parse_args(int argc, char* argv[]) {
    std::unique_ptr<Args> args = std::unique_ptr<Args>(new Args {
        .player1 = "",
        .player2 = "",
        .seed = static_cast<unsigned>(std::time(nullptr)),
        .max_depth = 4U,
        .rand = false,
        .verbose = true,
        .games = 1,
    });
    int opt = 0;
    while((opt = getopt(argc, argv, "p:g:s:d:rqh")) != -1) {
        switch(opt) {
            case 'p': {
                // set the type of one of the players
                std::string input(optarg);
                if(input == "AI" || input == "HUMAN" || input == "RANDOM") {
                    // if the first player is already set, set the second one
                    if(args->player1.empty()) {
                        args->player1 = input;
                    } else if(args->player2.empty()) {
                        args->player2 = input;
                    } else {
                        err("The maximum number of players in -p is 2.");
                    }
                } else {
                    err("Invalid player identifier in -p.");
                }
                break;
            }
            case 'g': {
                // set the number of games
                std::string input(optarg);
                try {
                    unsigned games = static_cast<unsigned>(std::stoul(input));
                    args->games = games;
                } catch(std::exception& e) {
                    err("Argument to -g must be a positive integer.");
                }
                break;
            }
            case 's': {
                // sets the seed of the random number generator
                std::string input(optarg);
                try {
                    unsigned seed = static_cast<unsigned>(std::stoul(input));
                    args->seed = seed;
                } catch(std::exception& e) {
                    err("Argument to -s must be a non-negative integer.");
                }
                break;
            }
            case 'd': {
                // sets the maximum depth of an AI player
                std::string input(optarg);
                try {
                    unsigned max_depth = static_cast<unsigned>(std::stoul(input));
                    args->max_depth = max_depth;
                } catch(std::exception& e) {
                    err("Argument to -d must be a non-negative integer.");
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
            case '?':
            case 'h': 
            default: {
                // print a help message
                std::cout << "Not yet implemented (\"help\")" << std::endl;
                exit(0);
            }
        }
    }
    // set default player to AI
    if(args->player1.empty()) {
        args->player1 = "AI";
    }
    if(args->player2.empty()) {
        args->player2 = "AI";
    }
    return args;
}

// makes a player from an identifier
std::unique_ptr<ur::Player> from_id(const std::string& id, ur::Color turn, unsigned max_depth) {
    if(id == "AI") {
        return std::make_unique<ur::AIPlayer>(turn, max_depth);
    }
    if(id == "HUMAN") {
        return std::make_unique<ur::HumanPlayer>(turn);
    }
    if(id == "RANDOM") {
        return std::make_unique<ur::RandomPlayer>();
    }
    throw std::logic_error("Bad player type");
}

void run(const std::unique_ptr<Args>& args) {
    // the random number generator of the app
    std::mt19937 app_rng(args->seed);
    std::uniform_int_distribution<int> col_dist(0, 1);
    // the scores of each player
    int score1 = 0;
    int score2 = 0;
    for(int i = 0; i < args->games; ++i) {
        int p1_color = 0;
        if(args->rand) {
            p1_color = col_dist(app_rng);
        }
        ur::Color color = (p1_color == 0 ? ur::Color::WHITE : ur::Color::BLACK);
        std::unique_ptr<ur::Player> white;
        std::unique_ptr<ur::Player> black;
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
    std::cout << "Player 1's Percentage: " << static_cast<double>(score1) / args->games << std::endl;
    std::cout << "Player 2's Percentage: " << static_cast<double>(score2) / args->games << std::endl;
}

int main(int argc, char* argv[]) {
    // parse args
    std::unique_ptr<Args> args = parse_args(argc, argv);
    // initialize library's rng
    ur::set_seed(args->seed);
    // run the program
    run(args);
    return 0;
}
