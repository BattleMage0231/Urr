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
    ur::players::ai_player h(ur::Color::WHITE);
    ur::players::random_player r(ur::Color::BLACK);
    ur::game game(h, r);
    cout << (game.start() == 1 ? "WHITE WON" : "BLACK WON") << endl;
    /*
    // test multiple
    int total = 0;
    int beat = 0;
    for(int i = 0; i < 50; ++i) {
        int color = rand() % 2;
        srand((i + seed) ^ seed);
        if(color == 0) {
            ur::players::ai_player a(ur::Color::WHITE);
            ur::players::random_player b(ur::Color::BLACK);
            ur::game game(a, b);
            if(game.start() == 1) {
                ++beat;
            }
            ++total;
        } else {
            ur::players::ai_player a(ur::Color::BLACK);
            ur::players::random_player b(ur::Color::WHITE);
            ur::game game(b, a);
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
