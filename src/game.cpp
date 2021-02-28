#include <ur/game.h>

namespace ur {
    game::game(player& white, player& black) : white_player(white), black_player(black) {
        b = board();
        white_turn = true;
    }

    player& game::get_player() {
        return white_turn ? white_player : black_player;
    }

    int game::get_move(int roll) {
        bool* pieces = b.get_pieces(white_turn);
        int rem = b.get_rem(white_turn);
        bool* opp_pieces = b.get_pieces(!white_turn);
        int opp_rem = b.get_rem(!white_turn);
        return get_player().get_move(
            pieces,
            rem,
            opp_pieces,
            opp_rem,
            roll
        );
    }

    void game::display_move(int roll, int tile) {
        using std::cout;
        using std::endl;
        cout << (white_turn ? "WHITE" : "BLACK") << " played " << tile << " with roll " << roll << endl;
    }

    void game::display_no_moves(int roll) {
        using std::cout;
        using std::endl;
        cout << (white_turn ? "WHITE" : "BLACK") << " had no valid moves for roll " << roll << endl;
    }

    void game::move() {
        //b.display_board();
        int roll = 0;
        for(int i = 0; i < 4; ++i) {
            roll += rand() % 2;
        }
        if(!b.has_valid(roll, white_turn)) {
            //display_no_moves(roll);
            b.no_moves(white_turn);
            white_turn = !white_turn;
            return;
        }
        int tile = get_move(roll);
        while(!b.is_valid(roll, tile, white_turn)) {
            tile = get_move(roll);
        }
        //display_move(roll, tile);
        b.move_piece(tile, tile + roll, white_turn);
        if(!b.is_rosette(tile + roll)) {
            white_turn = !white_turn;
        }
    }

    int game::start() {
        while(!b.winner()) {
            move();
        }
        return b.winner();
    }
}
