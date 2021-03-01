#include <ur/board.h>

namespace ur {
    Color opposite(Color t) {
        return (t == Color::WHITE) ? Color::BLACK : Color::WHITE;
    }

    board::board() {
        for(int i = 0; i < 14; ++i) {
            white_pieces[i] = false;
            black_pieces[i] = false;
        }
    }

    board::board(bool* white, int wrem, bool* black, int brem) {
        for(int i = 0; i < 14; ++i) {
            white_pieces[i] = white[i];
            black_pieces[i] = black[i];
        }
        white_rem = wrem;
        black_rem = brem;
    }

    bool* board::get_pieces(Color turn) {
        return (turn == Color::WHITE) ? white_pieces : black_pieces;
    }

    int board::get_rem(Color turn) {
        return (turn == Color::WHITE) ? white_rem : black_rem;
    }

    bool board::is_competition(int tile) {
        return 4 <= tile && tile <= 11;
    }

    bool board::is_rosette(int tile) {
        return tile == 3 || tile == 7 || tile == 12;
    }

    bool board::is_board(int tile) {
        return 0 <= tile && tile <= 13;
    }

    bool board::is_vulnerable(int tile,Color turn) {
        bool* opp_pieces = get_pieces(opposite(turn));
        return !(is_competition(tile) && is_rosette(tile) && opp_pieces[tile]);
    }

    bool board::has_valid(int roll, Color turn) {
        bool* pieces = get_pieces(turn);
        int rem = get_rem(turn);
        bool* opp_pieces = get_pieces(opposite(turn));
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
                        if(is_vulnerable(i + roll, turn)) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    bool board::is_valid(int roll, int tile, Color turn) {
        bool* pieces = get_pieces(turn);
        int rem = get_rem(turn);
        bool* opp_pieces = get_pieces(opposite(turn));
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
                return !pieces[tile + roll] && is_vulnerable(tile + roll, turn);
            } else {
                return false;
            }
        }
        return false;
    }

    int board::winner() {
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

    void board::change_rem(int value, Color turn) {
        if(turn == Color::WHITE) {
            white_rem += value;
        } else {
            black_rem += value;
        }
    }

    void board::display_board() {
        using std::cout;
        using std::endl;
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

    void board::undo_last() {
        move mov = moves.back();
        moves.pop_back();
        bool* pieces = get_pieces(mov.turn);
        bool* opp_pieces = get_pieces(opposite(mov.turn));
        if(!mov.has_move || mov.orig == mov.loc) {
            return;
        }
        if(mov.orig == -1) {
            pieces[mov.loc] = false;
            change_rem(1, mov.turn);
        } else if(mov.loc == 14) {
            pieces[mov.orig] = true;
        } else {
            pieces[mov.loc] = false;
            pieces[mov.orig] = true;
        }
        if(mov.took_piece) {
            change_rem(-1, opposite(mov.turn));
            opp_pieces[mov.loc] = true;
        }
    }

    void board::no_moves(Color turn) {
        moves.push_back(move {
            .has_move = false,
            .turn = turn,
            .orig = -2,
            .loc = -2,
            .took_piece = false
        });
    }

    void board::move_piece(int orig, int loc, Color turn) {
        bool* pieces = get_pieces(turn);
        int rem = get_rem(turn);
        bool* opp_pieces = get_pieces(opposite(turn));
        int opp_rem = get_rem(opposite(turn));
        move mov {
            .has_move = true,
            .turn = turn,
            .orig = orig,
            .loc = loc,
            .took_piece = false,
        };
        if(orig != loc) {
            if(loc == 14) {
                pieces[orig] = false;
            } else if(orig == -1) {
                change_rem(-1, turn);
                pieces[loc] = true;
                if(is_competition(loc) && opp_pieces[loc]) {
                    change_rem(1, opposite(turn));
                    opp_pieces[loc] = false;
                    mov.took_piece = true;
                }
            } else {
                pieces[orig] = false;
                pieces[loc] = true;
                if(is_competition(loc) && opp_pieces[loc]) {
                    change_rem(1, opposite(turn));
                    opp_pieces[loc] = false;
                    mov.took_piece = true;
                }
            }
        }
        moves.push_back(mov);
    }

    board::~board() {}
}
