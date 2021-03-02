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
        white_done = orig.white_done;
        black_done = orig.black_done;
    }

    bool* Board::get_pieces(Color turn) {
        return (turn == Color::WHITE) ? white_pieces : black_pieces;
    }

    int& Board::get_rem(Color turn) {
        return (turn == Color::WHITE) ? white_rem : black_rem;
    }

    int& Board::get_done(Color turn) {
        return (turn == Color::WHITE) ? white_done : black_done;
    }

    bool Board::is_invulnerable(int tile, Color turn) {
        return is_competition(tile) && is_rosette(tile) && get_pieces(turn)[tile];
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
                        if(!is_invulnerable(i + roll, opposite(turn))) {
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
            if(tile == OFF_BOARD && rem > 0) {
                return true;
            }
            if(is_board(tile) && pieces[tile]) {
                return true;
            }
            return false;
        }
        if(tile == OFF_BOARD) {
            return rem > 0 && !pieces[roll - 1];
        }
        if(pieces[tile]) {
            if(tile + roll == BOARD_SIZE) {
                return true;
            } else if(is_board(tile + roll)) {
                return !pieces[tile + roll] && !is_invulnerable(tile + roll, opposite(turn));
            } else {
                return false;
            }
        }
        return false;
    }

    bool Board::finished() {
        return white_done == NUM_PIECES || black_done == NUM_PIECES;
    }

    Color Board::get_winner() {
        if(!finished()) {
            throw;
        }
        return (white_done == NUM_PIECES) ? Color::WHITE : Color::BLACK;
    }

    void Board::display_board() {
        using std::cout;
        using std::endl;
        int idx = 0;
        while(!is_competition(idx)) {
            if(white_pieces[idx]) {
                cout << "* ";
            } else if(is_rosette(idx)) {
                cout << "_ ";
            } else {
                cout << ". ";
            }
            ++idx;
        }
        cout << "| ";
        while(is_competition(idx)) {
            cout << "  ";
            ++idx;
        }
        cout << "| ";
        while(idx < BOARD_SIZE) {
            if(white_pieces[idx]) {
                cout << "* ";
            } else if(is_rosette(idx)) {
                cout << "_ ";
            } else {
                cout << ". ";
            }
            ++idx;
        }
        cout << endl;
        idx = 0;
        while(!is_competition(idx)) {
            cout << "  ";
            ++idx;
        }
        cout << "| ";
        while(is_competition(idx)) {
            if(white_pieces[idx]) {
                cout << "* ";
            } else if(black_pieces[idx]) {
                cout << "+ ";
            } else if(is_rosette(idx)) {
                cout << "_ ";
            } else {
                cout << ". ";
            }
            ++idx;
        }
        cout << "| ";
        cout << endl;
        idx = 0;
        while(!is_competition(idx)) {
            if(black_pieces[idx]) {
                cout << "+ ";
            } else if(is_rosette(idx)) {
                cout << "_ ";
            } else {
                cout << ". ";
            }
            ++idx;
        }
        cout << "| ";
        while(is_competition(idx)) {
            cout << "  ";
            ++idx;
        }
        cout << "| ";
        while(idx < BOARD_SIZE) {
            if(black_pieces[idx]) {
                cout << "+ ";
            } else if(is_rosette(idx)) {
                cout << "_ ";
            } else {
                cout << ". ";
            }
            ++idx;
        }
        cout << endl;
        idx = 0;
        while(!is_competition(idx)) {
            cout << idx % 10 << " ";
            ++idx;
        }
        cout << "| ";
        while(is_competition(idx)) {
            cout << idx % 10 << " ";
            ++idx;
        }
        cout << "| ";
        while(idx < BOARD_SIZE) {
            cout << idx % 10 << " ";
            ++idx;
        }
        cout << endl;
    }

    void Board::undo_last() {
        Move mov = moves.back();
        moves.pop_back();
        bool* pieces = get_pieces(mov.turn);
        bool* opp_pieces = get_pieces(opposite(mov.turn));
        if(!mov.has_move || mov.orig == mov.loc) {
            return;
        }
        if(mov.orig == OFF_BOARD) {
            pieces[mov.loc] = false;
            ++get_rem(mov.turn);
        } else if(mov.loc == BOARD_SIZE) {
            pieces[mov.orig] = true;
            --get_done(mov.turn);
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
            .orig = NULL_POS,
            .loc = NULL_POS,
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
                ++get_done(turn);
            } else if(orig == OFF_BOARD) {
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
