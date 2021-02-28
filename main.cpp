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

struct ur_move {
    bool has_move;
    bool white_turn;
    int orig, loc;
    bool took_piece;
};

class ur_board {
    private:
        bool white_pieces[BOARD_SIZE];
        bool black_pieces[BOARD_SIZE];
        int white_rem = NUM_PIECES;
        int black_rem = NUM_PIECES;
        vector<ur_move> moves;
    public:
        ur_board() {
            memset(white_pieces, 0, sizeof(white_pieces));
            memset(black_pieces, 0, sizeof(black_pieces));
        }

        ur_board(bool* white, int wrem, bool* black, int brem) {
            for(int i = 0; i < 14; ++i) {
                white_pieces[i] = white[i];
                black_pieces[i] = black[i];
            }
            white_rem = wrem;
            black_rem = brem;
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

        // undo the last move made
        void undo_last() {
            ur_move move = moves.back();
            moves.pop_back();
            bool* pieces = get_pieces(move.white_turn);
            bool* opp_pieces = get_pieces(!move.white_turn);
            if(!move.has_move || move.orig == move.loc) {
                return;
            }
            if(move.orig == -1) {
                pieces[move.loc] = false;
                change_rem(1, move.white_turn);
            } else if(move.loc == 14) {
                pieces[move.orig] = true;
            } else {
                pieces[move.loc] = false;
                pieces[move.orig] = true;
            }
            if(move.took_piece) {
                change_rem(-1, !move.white_turn);
                opp_pieces[move.loc] = true;
            }
        }

        void no_moves(bool white_turn) {
            moves.push_back(ur_move {
                .has_move = false,
                .white_turn = white_turn,
                .orig = -2,
                .loc = -2,
                .took_piece = false
            });
        }

        void move_piece(int orig, int loc, bool white_turn) {
            bool* pieces = get_pieces(white_turn);
            int rem = get_rem(white_turn);
            bool* opp_pieces = get_pieces(!white_turn);
            int opp_rem = get_rem(!white_turn);
            ur_move move {
                .has_move = true,
                .white_turn = white_turn,
                .orig = orig,
                .loc = loc,
                .took_piece = false,
            };
            if(orig != loc) {
                if(loc == 14) {
                    pieces[orig] = false;
                } else if(orig == -1) {
                    change_rem(-1, white_turn);
                    pieces[loc] = true;
                    if(is_competition(loc) && opp_pieces[loc]) {
                        change_rem(1, !white_turn);
                        opp_pieces[loc] = false;
                        move.took_piece = true;
                    }
                } else {
                    pieces[orig] = false;
                    pieces[loc] = true;
                    if(is_competition(loc) && opp_pieces[loc]) {
                        change_rem(1, !white_turn);
                        opp_pieces[loc] = false;
                        move.took_piece = true;
                    }
                }
            }
            moves.push_back(move);
        }
};

class ur_game {
    private:
        ur_board board;
        ur_player& white_player;
        ur_player& black_player;
        bool white_turn;
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

        void display_no_moves(int roll) {
            cout << (white_turn ? "WHITE" : "BLACK") << " had no valid moves for roll " << roll << endl;
        }

        void move() {
            //board.display_board();
            int roll = 0;
            for(int i = 0; i < 4; ++i) {
                roll += rand() % 2;
            }
            if(!board.has_valid(roll, white_turn)) {
                display_no_moves(roll);
                board.no_moves(white_turn);
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

        int start() {
            while(!board.winner()) {
                move();
            }
            return board.winner();
        }
};

class ai_player : public virtual ur_player {
    private:
        bool is_white;
    public:
        ai_player(bool white) {
            is_white = white;
        }

        double value_of(ur_board& b, bool white_turn) {
            bool* pieces = b.get_pieces(white_turn);
            int rem = b.get_rem(white_turn);
            bool* opp_pieces = b.get_pieces(!white_turn);
            int opp_rem = b.get_rem(!white_turn);
            int board = 0;
            int opp_board = 0;
            double val = 0;
            double loc_vals[] = {
                1.02, 1.14, 1.31, 1.93, 1.28, 1.33, 1.38, 2.38, 1.46, 1.44, 1.38, 1.35, 2.20, 1.75
            };
            for(int i = 0; i < 14; ++i) {
                if(pieces[i]) {
                    ++board;
                    val += loc_vals[i];
                }
                if(opp_pieces[i]) {
                    ++opp_board;
                    val -= loc_vals[i];
                }
            }
            if(board == 0 && rem == 0) {
                return 1000.0;
            }
            if(opp_board == 0 && opp_rem == 0) {
                return -1000.0;
            }
            int done = 7 - board - rem;
            int opp_done = 7 - opp_board - opp_rem;
            return val + 10.0 * done + 2.0 * board - 10.0 * opp_done - 2.0 * opp_board;
        }

        double get_avg(ur_board& board, int depth, bool white_turn, double alpha, double beta) {
            double rates[] = {0.0625, 0.25, 0.375, 0.25, 0.0625};
            double ans = 0;
            for(int i = 0; i <= 4; ++i) {
                ans += rates[i] * negamax(board, i, white_turn, depth, alpha, beta).second;
            }
            return ans;
        }

        int find_any(bool* pieces, int rem) {
            if(rem > 0) {
                return -1;
            }
            for(int i = 0; i < 14; ++i) {
                if(pieces[i]) {
                    return i;
                }
            }
            throw -1;
        }

        pair<int, double> negamax(ur_board& board, int roll, bool white_turn, int depth, double alpha, double beta) {
            if(board.winner() || depth > 4) {
                return make_pair(-2, value_of(board, white_turn));
            }
            if(roll == 0) {
                int any_free = find_any(board.get_pieces(white_turn), board.get_rem(white_turn));
                board.move_piece(any_free, any_free + roll, white_turn);
                pair<int, double> ans = make_pair(any_free, -get_avg(board, depth + 1, !white_turn, -beta, -alpha));
                board.undo_last();
                return ans;
            }
            if(!board.has_valid(roll, white_turn)) {
                board.no_moves(white_turn);
                pair<int, double> ans = make_pair(-2, -get_avg(board, depth + 1, !white_turn, -beta, -alpha));
                board.undo_last();
                return ans;
            }
            vector<pair<double, int>> moves;
            for(int i = -1; i < 14; ++i) {
                if(board.is_valid(roll, i, white_turn)) {
                    board.move_piece(i, i + roll, white_turn);
                    if(!board.is_rosette(i + roll)) {
                        moves.push_back(make_pair(-value_of(board, !white_turn), i));
                    } else {
                        moves.push_back(make_pair(value_of(board, white_turn), i));
                    }
                    board.undo_last();
                }
            }
            sort(moves.begin(), moves.end());
            double cmax = -numeric_limits<double>::max();
            int mmax = -2;
            for(int i = (int) moves.size() - 1; i >= 0; --i) {
                int tile = moves[i].second;
                if(!board.is_valid(roll, tile, white_turn)) {
                    throw tile;
                }
                board.move_piece(tile, tile + roll, white_turn);
                double ans;
                if(!board.is_rosette(tile + roll)) {
                    ans = -get_avg(board, depth + 1, !white_turn, -beta, -alpha);
                } else {
                    ans = get_avg(board, depth + 1, white_turn, alpha, beta);
                }
                board.undo_last();
                if(ans >= cmax) {
                    cmax = ans;
                    mmax = tile;
                }
                alpha = max(alpha, cmax);
                if(beta <= alpha) {
                    break;
                }
            }
            return make_pair(mmax, cmax);
        }

        int get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll) {
            if(roll == 0) {
                return find_any(pieces, rem);
            }
            if(rem > 0) {
                bool any = false;
                for(int i = 0; i < 14; ++i) {
                    if(pieces[i]) {
                        any = true;
                        break;
                    }
                }
                if(!any) {
                    return -1;
                }
            }
            ur_board board;
            if(is_white) {
                board = ur_board(pieces, rem, opp_pieces, opp_rem);
            } else {
                board = ur_board(opp_pieces, opp_rem, pieces, rem);
            }
            double inf = numeric_limits<double>::max();
            double neginf = -inf;
            pair<int, double> ans = negamax(board, roll, is_white, 0, neginf, inf);
            return ans.first;
        }
};

int main(int argc, char* argv[]) {
    int seed = time(NULL);
    if(argc > 1) {
        seed = atoi(argv[1]);
    }
    cout << "Seed: " << seed << endl;
    // test one
    srand(seed);
    ai_player h(true);
    ai_player r(false);
    ur_game game(h, r);
    cout << (game.start() == 1 ? "WHITE WON" : "BLACK WON") << endl;
    /*
    // test multiple
    int total = 0;
    int beat = 0;
    for(int i = 0; i < 50; ++i) {
        int color = rand() % 2;
        srand(i ^ seed);
        if(color == 0) {
            ai_player a(true);
            random_player b(false);
            ur_game game(a, b);
            if(game.start() == 1) {
                ++beat;
            }
            ++total;
        } else {
            ai_player a(false);
            random_player b(true);
            ur_game game(b, a);
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
