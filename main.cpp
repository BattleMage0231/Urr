#include <bits/stdc++.h>

using namespace std;

constexpr int BOARD_SIZE = 14;
constexpr int NUM_PIECES = 7;

class ur_player {
    public:
        virtual int get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll) = 0;
};

class human_player : public virtual ur_player {
    private:
        bool is_white;
    public:
        human_player(bool white) {
            is_white = white;
        }

        int get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll) {
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
};

class random_player : public virtual ur_player {
    public:
        random_player(bool white) {}

        int get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll) {
            return (rand() % 15) - 1;
        }
};

class ur_move {};

class ur_board {
    private:
        bool white_pieces[BOARD_SIZE];
        bool black_pieces[BOARD_SIZE];
        int white_rem = NUM_PIECES;
        int black_rem = NUM_PIECES;
    public:
        ur_board() {
            memset(white_pieces, 0, sizeof(white_pieces));
            memset(black_pieces, 0, sizeof(black_pieces));
        }

        bool* get_pieces(bool white_turn) {
            if(white_turn) {
                return white_pieces;
            } else {
                return black_pieces;
            }
        }

        int get_rem(bool white_turn) {
            if(white_turn) {
                return white_rem;
            } else {
                return black_rem;
            }
        }

        bool is_competition(int tile) {
            return 4 <= tile && tile <= 11;
        }

        bool is_rosette(int tile) {
            return tile == 3 || tile == 7 || tile == 12;
        }

        bool is_board(int tile) {
            return 0 <= tile && tile <= 13;
        }

        bool is_vulnerable(int tile, bool white_turn) {
            bool* opp_pieces = get_pieces(!white_turn);
            return !(is_competition(tile) && is_rosette(tile) && opp_pieces[tile]);
        }

        bool has_valid(int roll, bool white_turn) {
            bool* pieces = get_pieces(white_turn);
            int rem = get_rem(white_turn);
            bool* opp_pieces = get_pieces(!white_turn);
            if(roll == 0) {
                return true;
            }
            if(rem > 0 && !pieces[roll - 1]) {
                return true;
            }
            for(int i = 0; i < 14; ++i) {
                if(pieces[i]) {
                    if(i + roll == 14) {
                        return true;
                    } else if(is_board(i + roll)) {
                        if(!pieces[i + roll]) {
                            if(is_vulnerable(i + roll, white_turn)) {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }

        bool is_valid(int roll, int tile, bool white_turn) {
            bool* pieces = get_pieces(white_turn);
            int rem = get_rem(white_turn);
            bool* opp_pieces = get_pieces(!white_turn);
            if(roll == 0) {
                if(tile == -1 && rem > 0) {
                    return true;
                }
                if(is_board(tile) && pieces[tile]) {
                    return true;
                }
                return false;
            }
            if(tile == -1) {
                return rem > 0 && !pieces[roll - 1];
            }
            if(pieces[tile]) {
                if(tile + roll == 14) {
                    return true;
                } else if(is_board(tile + roll)) {
                    return !pieces[tile + roll] && is_vulnerable(tile + roll, white_turn);
                } else {
                    return false;
                }
            }
            return false;
        }

        int winner() {
            bool white = (white_rem == 0);
            bool black = (black_rem == 0);
            if(!white && !black) {
                return 0;
            }
            for(int i = 0; i < 14; ++i) {
                if(white_pieces[i]) {
                    white = false;
                }
                if(black_pieces[i]) {
                    black = false;
                }
            }
            if(white) {
                return 1;
            }
            if(black) {
                return 2;
            }
            return 0;
        }

        void change_rem(int value, bool white_turn) {
            if(white_turn) {
                white_rem += value;
            } else {
                black_rem += value;
            }
        }

        void display_board() {
            for(int i = 0; i < 4; ++i) {
                if(white_pieces[i]) {
                    cout << "* ";
                } else if(is_rosette(i)) {
                    cout << "_ ";
                } else {
                    cout << ". ";
                }
            }
            cout << "| ";
            for(int i = 0; i < 16; ++i) {
                cout << ' ';
            }
            cout << "| ";
            for(int i = 12; i < 14; ++i) {
                if(white_pieces[i]) {
                    cout << "* ";
                } else if(is_rosette(i)) {
                    cout << "_ ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
            for(int i = 0; i < 8; ++i) {
                cout << ' ';
            }
            cout << "| ";
            for(int i = 4; i < 12; ++i) {
                if(white_pieces[i]) {
                    cout << "* ";
                } else if(black_pieces[i]) {
                    cout << "+ ";
                } else if(is_rosette(i)) {
                    cout << "_ ";
                } else {
                    cout << ". ";
                }
            }
            cout << "|" << endl;
            for(int i = 0; i < 4; ++i) {
                if(black_pieces[i]) {
                    cout << "+ ";
                } else if(is_rosette(i)) {
                    cout << "_ ";
                } else {
                    cout << ". ";
                }
            }
            cout << "| ";
            for(int i = 0; i < 16; ++i) {
                cout << ' ';
            }
            cout << "| ";
            for(int i = 12; i < 14; ++i) {
                if(black_pieces[i]) {
                    cout << "+ ";
                } else if(is_rosette(i)) {
                    cout << "_ ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
            for(int i = 0; i < 4; ++i) {
                cout << i << ' ';
            }
            cout << "| ";
            for(int i = 4; i < 12; ++i) {
                cout << i % 10 << ' ';
            }
            cout << "| ";
            for(int i = 12; i < 14; ++i) {
                cout << i % 10 << ' ';
            }
            cout << endl << endl;
        }

        void move_piece(int orig, int loc, bool white_turn) {
            bool* pieces = get_pieces(white_turn);
            int rem = get_rem(white_turn);
            bool* opp_pieces = get_pieces(!white_turn);
            int opp_rem = get_rem(!white_turn);
            if(orig != loc) {
                if(loc == 14) {
                    pieces[orig] = false;
                } else if(orig == -1) {
                    change_rem(-1, white_turn);
                    pieces[loc] = true;
                    if(is_competition(loc) && opp_pieces[loc]) {
                        change_rem(1, !white_turn);
                        opp_pieces[loc] = false;
                    }
                } else {
                    pieces[orig] = false;
                    pieces[loc] = true;
                    if(is_competition(loc) && opp_pieces[loc]) {
                        change_rem(1, !white_turn);
                        opp_pieces[loc] = false;
                    }
                }
            }
        }
};

class ur_game {
    private:
        ur_board board;
        ur_player& white_player;
        ur_player& black_player;
        bool white_turn;
        vector<ur_move> moves;
    public:
        ur_game(ur_player& white, ur_player& black) : white_player(white), black_player(black) {
            board = ur_board();
            white_turn = true;
        }

        ur_player& get_player() {
            if(white_turn) {
                return white_player;
            } else {
                return black_player;
            }
        }

        int get_move(int roll) {
            bool* pieces = board.get_pieces(white_turn);
            int rem = board.get_rem(white_turn);
            bool* opp_pieces = board.get_pieces(!white_turn);
            int opp_rem = board.get_rem(!white_turn);
            return get_player().get_move(
                pieces,
                rem,
                opp_pieces,
                opp_rem,
                roll
            );
        }

        void display_move(int roll, int tile) {
            cout << (white_turn ? "WHITE" : "BLACK") << " played " << tile << " with roll " << roll << endl;
        }

        void no_moves(int roll) {
            cout << (white_turn ? "WHITE" : "BLACK") << " had no valid moves for roll " << roll << endl;
        }

        // storing metadata is not implemented yet
        void move() {
            board.display_board();
            int roll = 0;
            for(int i = 0; i < 4; ++i) {
                roll += rand() % 2;
            }
            if(!board.has_valid(roll, white_turn)) {
                no_moves(roll);
                white_turn = !white_turn;
                return;
            }
            int tile = get_move(roll);
            while(!board.is_valid(roll, tile, white_turn)) {
                tile = get_move(roll);
            }
            display_move(roll, tile);
            board.move_piece(tile, tile + roll, white_turn);
            if(!board.is_rosette(tile + roll)) {
                white_turn = !white_turn;
            }
        }

        // not yet implemented
        void undo() {}

        int start() {
            while(!board.winner()) {
                move();
            }
            return board.winner();
        }
};

int main(int argc, char* argv[]) {
    int seed = time(NULL);
    if(argc > 1) {
        seed = atoi(argv[1]);
    }
    srand(seed);
    random_player h(true);
    random_player r(false);
    ur_game game(h, r);
    cout << (game.start() == 1 ? "WHITE WON" : "BLACK WON") << endl;
    cout << "Program end." << endl;
    return 0;
}
