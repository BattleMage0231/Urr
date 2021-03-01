#include <ur/board.h>

namespace ur {
    Board::Board() {
        for(int i = 0; i < BOARD_SIZE; ++i) {
            white_pieces[i] = false;
            black_pieces[i] = false;
        }
    }

    Board::Board(const Board& orig) {
        for(int i = 0; i < BOARD_SIZE; ++i) {
            white_pieces[i] = orig.white_pieces[i];
            black_pieces[i] = orig.black_pieces[i];
        }
        white_rem = orig.white_rem;
        black_rem = orig.black_rem;
    }

    bool* Board::get_pieces(Color turn) {
        return (turn == Color::WHITE) ? white_pieces : black_pieces;
    }

    int& Board::get_rem(Color turn) {
        return (turn == Color::WHITE) ? white_rem : black_rem;
    }

    bool Board::is_vulnerable(int tile, Color turn) {
        bool* opp_pieces = get_pieces(opposite(turn));
        return !(is_competition(tile) && is_rosette(tile) && opp_pieces[tile]);
    }

    bool Board::has_valid(int roll, Color turn) {
        bool* pieces = get_pieces(turn);
        int rem = get_rem(turn);
        bool* opp_pieces = get_pieces(opposite(turn));
        if(roll == 0) {
            return true;
        }
        if(rem > 0 && !pieces[roll - 1]) {
            return true;
        }
        for(int i = 0; i < BOARD_SIZE; ++i) {
            if(pieces[i]) {
                if(i + roll == BOARD_SIZE) {
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

    bool Board::is_valid(int roll, int tile, Color turn) {
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
            if(tile + roll == BOARD_SIZE) {
                return true;
            } else if(is_board(tile + roll)) {
                return !pieces[tile + roll] && is_vulnerable(tile + roll, turn);
            } else {
                return false;
            }
        }
        return false;
    }

    int Board::winner() {
        bool white = (white_rem == 0);
        bool black = (black_rem == 0);
        if(!white && !black) {
            return 0;
        }
        for(int i = 0; i < BOARD_SIZE; ++i) {
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

    // TODO change this to depend on NUM_PIECES and BOARD_SIZE
    void Board::display_board() {
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

    void Board::undo_last() {
        Move mov = moves.back();
        moves.pop_back();
        bool* pieces = get_pieces(mov.turn);
        bool* opp_pieces = get_pieces(opposite(mov.turn));
        if(!mov.has_move || mov.orig == mov.loc) {
            return;
        }
        if(mov.orig == -1) {
            pieces[mov.loc] = false;
            ++get_rem(mov.turn);
        } else if(mov.loc == 14) {
            pieces[mov.orig] = true;
        } else {
            pieces[mov.loc] = false;
            pieces[mov.orig] = true;
        }
        if(mov.took_piece) {
            --get_rem(opposite(mov.turn));
            opp_pieces[mov.loc] = true;
        }
    }

    void Board::no_moves(Color turn) {
        moves.push_back(Move {
            .has_move = false,
            .turn = turn,
            .orig = -2,
            .loc = -2,
            .took_piece = false
        });
    }

    void Board::move_piece(int orig, int loc, Color turn) {
        bool* pieces = get_pieces(turn);
        int rem = get_rem(turn);
        bool* opp_pieces = get_pieces(opposite(turn));
        int opp_rem = get_rem(opposite(turn));
        Move mov {
            .has_move = true,
            .turn = turn,
            .orig = orig,
            .loc = loc,
            .took_piece = false,
        };
        if(orig != loc) {
            if(loc == BOARD_SIZE) {
                pieces[orig] = false;
            } else if(orig == -1) {
                --get_rem(turn);
                pieces[loc] = true;
                if(is_competition(loc) && opp_pieces[loc]) {
                    ++get_rem(opposite(turn));
                    opp_pieces[loc] = false;
                    mov.took_piece = true;
                }
            } else {
                pieces[orig] = false;
                pieces[loc] = true;
                if(is_competition(loc) && opp_pieces[loc]) {
                    ++get_rem(opposite(turn));
                    opp_pieces[loc] = false;
                    mov.took_piece = true;
                }
            }
        }
        moves.push_back(mov);
    }

    Board::~Board() {}
}
