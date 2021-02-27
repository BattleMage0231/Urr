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
        ur_player& white_player;
        ur_player& black_player;
        bool white_turn;
        vector<ur_move> moves;
    public:
        ur_board(ur_player& white, ur_player& black) : white_player(white), black_player(black) {
            memset(white_pieces, 0, sizeof(white_pieces));
            memset(black_pieces, 0, sizeof(black_pieces));
            white_turn = true;
        }

        pair<bool*, int> get_cur() {
            if(white_turn) {
                return make_pair(white_pieces, white_rem);
            } else {
                return make_pair(black_pieces, black_rem);
            }
        }

        pair<bool*, int> get_opp() {
            if(white_turn) {
                return make_pair(black_pieces, black_rem);
            } else {
                return make_pair(white_pieces, white_rem);
            }
        }

        ur_player& get_player() {
            if(white_turn) {
                return white_player;
            } else {
                return black_player;
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

        bool is_vulnerable(int tile) {
            pair<bool*, int> opp = get_opp();
            bool* opp_pieces = opp.first;
            return !(is_competition(tile) && is_rosette(tile) && opp_pieces[tile]);
        }

        bool has_valid(int roll) {
            pair<bool*, int> cur = get_cur(), opp = get_opp();
            bool* pieces = cur.first;
            int rem = cur.second;
            bool* opp_pieces = opp.first;
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
                            if(is_vulnerable(i + roll)) {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }

        bool is_valid(int roll, int tile) {
            pair<bool*, int> cur = get_cur(), opp = get_opp();
            bool* pieces = cur.first;
            int rem = cur.second;
            bool* opp_pieces = opp.first;
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
                    return !pieces[tile + roll] && is_vulnerable(tile + roll);
                } else {
                    return false;
                }
            }
            return false;
        }

        int get_move(int roll) {
            pair<bool*, int> cur = get_cur(), opp = get_opp();
            return get_player().get_move(
                cur.first,
                cur.second,
                opp.first,
                opp.second,
                roll
            );
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

        void change_rem(int value, bool cur_player=true) {
            if(white_turn) {
                if(cur_player) {
                    white_rem += value;
                } else {
                    black_rem += value;
                }
            } else {
                if(cur_player) {
                    black_rem += value;
                } else {
                    white_rem += value;
                }
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

        void display_move(int roll, int tile=-2) {
            if(tile == -2) {
                cout << (white_turn ? "WHITE" : "BLACK") << " had no valid moves for roll " << roll << endl;
            } else {
                cout << (white_turn ? "WHITE" : "BLACK") << " played " << tile << " with roll " << roll << endl;
            }
        }

        // storing metadata is not implemented yet
        void move_piece(int orig, int loc) {
            pair<bool*, int> cur = get_cur(), opp = get_opp();
            bool* pieces = cur.first;
            int rem = cur.second;
            bool* opp_pieces = opp.first;
            int opp_rem = opp.second;
            if(orig != loc) {
                if(loc == 14) {
                    pieces[orig] = false;
                } else if(orig == -1) {
                    change_rem(-1, true);
                    pieces[loc] = true;
                    if(is_competition(loc) && opp_pieces[loc]) {
                        change_rem(1, false);
                        opp_pieces[loc] = false;
                    }
                } else {
                    pieces[orig] = false;
                    pieces[loc] = true;
                    if(is_competition(loc) && opp_pieces[loc]) {
                        change_rem(1, false);
                        opp_pieces[loc] = false;
                    }
                }
            }
        }

        // undo is not yet implemented
        void undo() {}

        // storing metadata is not implemented yet
        void move() {
            display_board();
            int roll = 0;
            for(int i = 0; i < 4; ++i) {
                roll += rand() % 2;
            }
            if(!has_valid(roll)) {
                display_move(roll);
                white_turn = !white_turn;
                return;
            }
            int tile = get_move(roll);
            while(!is_valid(roll, tile)) {
                tile = get_move(roll);
            }
            display_move(roll, tile);
            move_piece(tile, tile + roll);
            if(!is_rosette(tile + roll)) {
                white_turn = !white_turn;
            }
        }

        int start() {
            while(!winner()) {
                move();
            }
            return winner();
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
    ur_board b(h, r);
    cout << (b.start() == 1 ? "WHITE WON" : "BLACK WON") << endl;
    cout << "Program end." << endl;
    return 0;
}
