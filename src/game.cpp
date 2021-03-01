#include <ur/game.h>

namespace ur {
    game::game(players::player& white, players::player& black) : white_player(white), black_player(black) {
        b = board();
        turn = Color::WHITE;
    }

    players::player& game::get_player() {
        return (turn == Color::WHITE) ? white_player : black_player;
    }

    int game::get_move(int roll) {
        board clone(b);
        return get_player().get_move(clone, roll);
    }

    void game::display_move(int roll, int tile) {
        using std::cout;
        using std::endl;
        cout << ((turn == Color::WHITE) ? "WHITE" : "BLACK") << " played " << tile << " with roll " << roll << endl;
    }

    void game::display_no_moves(int roll) {
        using std::cout;
        using std::endl;
        cout << ((turn == Color::WHITE) ? "WHITE" : "BLACK") << " had no valid moves for roll " << roll << endl;
    }

    void game::move() {
        b.display_board();
        int roll = 0;
        for(int i = 0; i < 4; ++i) {
            roll += rand() % 2;
        }
        if(!b.has_valid(roll, turn)) {
            display_no_moves(roll);
            b.no_moves(turn);
            turn = opposite(turn);
            return;
        }
        int tile = get_move(roll);
        while(!b.is_valid(roll, tile, turn)) {
            tile = get_move(roll);
        }
        display_move(roll, tile);
        b.move_piece(tile, tile + roll, turn);
        if(!is_rosette(tile + roll)) {
            turn = opposite(turn);
        }
    }

    int game::start() {
        while(!b.winner()) {
            move();
        }
        return b.winner();
    }
}
