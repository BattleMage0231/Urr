#include <ur/board.h>

// to easily access a variable by a player color
#define rem(turn) ((turn == Color::WHITE) ? white_rem : black_rem)
#define done(turn) ((turn == Color::WHITE) ? white_done : black_done)
#define pieces(turn) ((turn == Color::WHITE) ? white_pieces : black_pieces)

namespace ur {
    Board::Board() noexcept
        : white_rem(NUM_PIECES)
        , black_rem(NUM_PIECES)
        , white_done(0)
        , black_done(0)
    {
        white_pieces.fill(false);
        black_pieces.fill(false);
    }

    Board::Board(const Board& orig) noexcept 
        : white_pieces(orig.white_pieces) // copy constructor of std::array is called
        , black_pieces(orig.black_pieces) // they will point to different arrays
        , white_rem(orig.white_rem)
        , black_rem(orig.black_rem)
        , white_done(orig.white_done)
        , black_done(orig.black_done)
    {}

    bool Board::has_piece(int tile, Color turn) const {
        return pieces(turn).at(tile);
    }

    int Board::get_rem(Color turn) const noexcept {
        return (turn == Color::WHITE) ? white_rem : black_rem;
    }

    int Board::get_done(Color turn) const noexcept {
        return (turn == Color::WHITE) ? white_done : black_done;
    }

    bool Board::is_invulnerable(int tile, Color turn) const {
        return is_competition(tile) && is_rosette(tile) && has_piece(tile, turn);
    }

    bool Board::has_valid(int roll, Color turn) const {
        if(roll < 0) {
            throw std::invalid_argument("Roll value must be non-negative");
        }
        int rem = get_rem(turn);
        // there is always a possible move if roll = 0
        if(roll == 0) {
            return true;
        }
        if(rem > 0 && !has_piece(roll - 1, turn)) {
            return true;
        }
        for(int i = 0; i < BOARD_SIZE; ++i) {
            if(has_piece(i, turn)) {
                if(i + roll == BOARD_SIZE) {
                    return true;
                } else if(is_board(i + roll)) {
                    // if there is no piece blocking this one from moving
                    if(!has_piece(i + roll, turn)) {
                        // if there is no invulnerable opponent piece at the destination
                        if(!is_invulnerable(i + roll, opposite(turn))) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    bool Board::is_valid(int roll, int tile, Color turn) const {
        if(roll < 0) {
            throw std::invalid_argument("Roll value must be non-negative");
        }
        if(!tile_exists(tile)) {
            throw std::invalid_argument("Tile must be a valid value");
        }
        int rem = get_rem(turn);
        if(roll == 0) {
            if(tile == OFF_BOARD && rem > 0) {
                return true;
            }
            if(is_board(tile) && has_piece(tile, turn)) {
                return true;
            }
            return false;
        }
        if(tile == OFF_BOARD) {
            return rem > 0 && !has_piece(roll - 1, turn);
        }
        if(has_piece(tile, turn)) {
            if(tile + roll == BOARD_SIZE) {
                return true;
            } else if(is_board(tile + roll)) {
                // check that there is no piece blocking this one from moving
                // and there is no invulnerable opponent piece at the destination
                return !has_piece(tile + roll, turn) && !is_invulnerable(tile + roll, opposite(turn));
            } else {
                return false;
            }
        }
        return false;
    }

    bool Board::finished() const noexcept {
        return white_done == NUM_PIECES || black_done == NUM_PIECES;
    }

    Color Board::get_winner() const {
        if(!finished()) {
            throw std::logic_error("Game must have finished to call get_winner");
        }
        return (white_done == NUM_PIECES) ? Color::WHITE : Color::BLACK;
    }

    void Board::display_board() const noexcept {
        // display first line (white safe zone)
        for(int i = 0; i < BOARD_SIZE; ++i) {
            if(i == 4 || i == 12) {
                std::cout << "| ";
            }
            if(i >= 4 && i < 12) {
                std::cout << "  ";
                continue;
            }
            if(white_pieces[i]) {
                std::cout << "* ";
            } else if(black_pieces[i] && is_competition(i)) {
                std::cout << "+ ";
            } else if(is_rosette(i)) {
                std::cout << "_ ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
        // display second line (competition zone)
        for(int i = 0; i < BOARD_SIZE; ++i) {
            if(i == 4 || i == 12) {
                std::cout << "| ";
            }
            if(i < 4 || i >= 12) {
                std::cout << "  ";
                continue;
            }
            if(white_pieces[i]) {
                std::cout << "* ";
            } else if(black_pieces[i]) {
                std::cout << "+ ";
            } else if(is_rosette(i)) {
                std::cout << "_ ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
        // display third line (black safe zone)
        for(int i = 0; i < BOARD_SIZE; ++i) {
            if(i == 4 || i == 12) {
                std::cout << "| ";
            }
            if(i >= 4 && i < 12) {
                std::cout << "  ";
                continue;
            }
            if(black_pieces[i]) {
                std::cout << "+ ";
            } else if(white_pieces[i] && is_competition(i)) {
                std::cout << "* ";
            } else if(is_rosette(i)) {
                std::cout << "_ ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
        // display fourth line (indices)
        for(int i = 0; i < BOARD_SIZE; ++i) {
            if(i == 4 || i == 12) {
                std::cout << "| ";
            }
            std::cout << i % 10 << " ";
        }
        std::cout << std::endl;
    }

    void Board::undo_last() {
        // get the last move
        Move mov = moves.back();
        moves.pop_back();
        // the move didn't have any effect
        if(!mov.has_move || mov.orig == mov.loc) {
            return;
        }
        if(mov.orig == OFF_BOARD) {
            // move the piece back off board
            pieces(mov.turn)[mov.loc] = false;
            ++rem(mov.turn);
        } else if(mov.loc == BOARD_SIZE) {
            // move the finished piece back on the board
            pieces(mov.turn)[mov.orig] = true;
            --done(mov.turn);
        } else {
            // move the piece back to its original position
            pieces(mov.turn)[mov.loc] = false;
            pieces(mov.turn)[mov.orig] = true;
        }
        if(mov.took_piece) {
            // untake an opponent piece
            --rem(opposite(mov.turn));
            pieces(opposite(mov.turn))[mov.loc] = true;
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
        if(!tile_exists(orig) || (!tile_exists(loc) && loc != 14)) {
            throw std::invalid_argument("Tile must be a valid value");
        }
        Move mov {
            .has_move = true,
            .turn = turn,
            .orig = orig,
            .loc = loc,
            .took_piece = false,
        };
        if(orig != loc) {
            if(loc == BOARD_SIZE) {
                // move the finished piece off board
                pieces(turn)[orig] = false;
                ++done(turn);
            } else if(orig == OFF_BOARD) {
                // move the piece onto the board
                --rem(turn);
                pieces(turn)[loc] = true;
                // possible take an opponent piece
                if(is_competition(loc) && has_piece(loc, opposite(turn))) {
                    ++rem(opposite(turn));
                    pieces(opposite(turn))[loc] = false;
                    mov.took_piece = true;
                }
            } else {
                // move the piece to its new location
                pieces(turn)[orig] = false;
                pieces(turn)[loc] = true;
                // possible take an opponent piece
                if(is_competition(loc) && has_piece(loc, opposite(turn))) {
                    ++rem(opposite(turn));
                    pieces(opposite(turn))[loc] = false;
                    mov.took_piece = true;
                }
            }
        }
        moves.push_back(mov);
    }
}
