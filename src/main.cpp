#include <ur/ur.h>

#include <ctime>
#include <cstdlib>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    using std::cout;
    using std::endl;
    int seed = std::time(nullptr);
    if(argc > 1) {
        seed = std::atoi(argv[1]);
    }
    cout << "Seed: " << seed << endl;
    // test one
    srand(seed);
    ur::players::AIPlayer h(ur::Color::WHITE);
    ur::players::RandomPlayer r(ur::Color::BLACK);
    ur::Game game(h, r);
    cout << (game.start() == 1 ? "WHITE WON" : "BLACK WON") << endl;
    /*
    // test multiple
    int total = 0;
    int beat = 0;
    for(int i = 0; i < 50; ++i) {
        int color = rand() % 2;
        srand((i + seed) ^ seed);
        if(color == 0) {
            ur::players::AIPlayer a(ur::Color::WHITE);
            ur::players::RandomPlayer b(ur::Color::BLACK);
            ur::Game game(a, b);
            if(game.start() == 1) {
                ++beat;
            }
            ++total;
        } else {
            ur::players::AIPlayer a(ur::Color::BLACK);
            ur::players::RandomPlayer b(ur::Color::WHITE);
            ur::Game game(b, a);
            if(game.start() == 2) {
                ++beat;
            }
            ++total;
        }
        cout << "Finished match " << i + 1 << " with " << (double) beat / total << endl;
    }
    cout << (double) beat / total << endl;
    */
    cout << "Program end." << endl;
    return 0;
}
