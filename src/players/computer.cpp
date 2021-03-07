#include <ur/players/computer.h>

namespace ur {
    bool AIPlayer::Node::operator <(const AIPlayer::Node& other) const {
        return value < other.value;
    }

    AIPlayer::AIPlayer(Color turn)
        : player_turn(turn) 
        , max_depth(4U) // the default maximum depth is 4
    {}

    AIPlayer::AIPlayer(Color turn, unsigned depth)
        : player_turn(turn) 
        , max_depth(depth)
    {}

    int AIPlayer::any_free(const Board& b, Color turn) {
        // check if there are any off board pieces
        if(b.get_rem(turn) > 0) {
            return OFF_BOARD;
        }
        // check for on board pieces
        for(int i = 0; i < BOARD_SIZE; ++i) {
            if(b.has_piece(i, turn)) {
                return i;
            }
        }
        throw std::logic_error("Expected at least one free piece");
    }

    double AIPlayer::get_avg(Board& b, unsigned depth, Color turn, double alpha, double beta) const {
        // chances of each roll happening
        double ans = 0;
        // do negamax for each possible roll
        for(int i = 0; i <= NUM_DICE; ++i) {
            ans += RATES[i] * negamax(b, i, turn, depth, alpha, beta).value;
        }
        return ans;
    }

    AIPlayer::Node AIPlayer::negamax(Board& b, int roll, Color turn, unsigned depth, double alpha, double beta) const {
        // negamax has reached its maximum depth or the game is finished
        if(b.finished() || depth > max_depth) {
            return Node {
                .pos = NULL_POS,
                .value = value_of(b, turn)
            };
        }
        // the roll is 0, meaning moving any piece will result in the same position
        if(roll == 0) {
            int free_piece = any_free(b, turn); // get any free piece
            b.move_piece(free_piece, free_piece + roll, turn);
            // run negamax on the corresponding position
            double avg = -get_avg(b, depth + 1, opposite(turn), -beta, -alpha);
            b.undo_last();
            return Node {
                .pos = free_piece,
                .value = avg
            };
        }
        // there are no valid moves
        if(!b.has_valid(roll, turn)) {
            b.no_moves(turn);
            // run negamax on the corresponding position
            double avg = -get_avg(b, depth + 1, opposite(turn), -beta, -alpha);
            b.undo_last();
            return Node {
                .pos = NULL_POS,
                .value = avg
            };
        }
        std::vector<Node> moves;
        // find all the valid moves
        for(int i = OFF_BOARD; i < BOARD_SIZE; ++i) {
            if(b.is_valid(roll, i, turn)) {
                b.move_piece(i, i + roll, turn);
                Node cur { .pos = i };
                // calculate the value of the position
                // if landing on a rosette tile, maximize next move because we can move again
                if(!is_rosette(i + roll)) {
                    cur.value = -value_of(b, opposite(turn));
                } else {
                    cur.value = value_of(b, turn);
                }
                moves.push_back(cur);
                b.undo_last();
            }
        }
        // reorder the moves by value
        std::sort(moves.begin(), moves.end());
        int mmax = NULL_POS; // the move giving the maximum value for player
        double cmax = NEGINF; // the value of the move
        // iterate over the moves from the back, traversing the best positions first
        for(auto it = moves.rbegin(); it != moves.rend(); ++it) {
            int tile = (*it).pos;
            b.move_piece(tile, tile + roll, turn);
            double ans = 0.0;
            if(!is_rosette(tile + roll)) {
                // minimize next move since the opponent is moving
                ans = -get_avg(b, depth + 1, opposite(turn), -beta, -alpha);
            } else {
                // if landing on a rosette tile, maximize next move because we can move again
                ans = get_avg(b, depth + 1, turn, alpha, beta);
            }
            b.undo_last();
            // take the maximum valued move
            if(ans >= cmax) {
                cmax = ans;
                mmax = tile;
            }
            // do alpha beta pruning
            alpha = std::max(alpha, cmax);
            // we can stop early if the alpha value satisfies this condition
            if(beta <= alpha) {
                break;
            }
        }
        return Node {
            .pos = mmax,
            .value = cmax
        };
    }

    double AIPlayer::value_of(const Board& b, Color turn) {
        double val = 0;
        for(int i = 0; i < BOARD_SIZE; ++i) {
            // add if we have a piece on this tile
            if(b.has_piece(i, turn)) {
                val += LOC_VALS[i];
            }
            // subtract if our opponent has a piece on this tile
            if(b.has_piece(i, opposite(turn))) {
                val -= LOC_VALS[i];
            }
        }
        int rem = b.get_rem(turn);
        int opp_rem = b.get_rem(opposite(turn));
        int done = b.get_done(turn);
        int opp_done = b.get_done(opposite(turn));
        int board = NUM_PIECES - rem - done;
        int opp_board = NUM_PIECES - opp_rem - opp_done;
        // additional calculations
        val += FINISHED_VALUE * done + BOARD_VALUE * board;
        val -= FINISHED_VALUE * opp_done - BOARD_VALUE * opp_board;
        return val;
    }

    int AIPlayer::get_move(Board& b, int roll) {
        if(roll < 0) {
            throw std::invalid_argument("Roll value must be non-negative");
        }
        // we don't need to calculate if the roll is 0
        // if we call negamax with this, it will still traverse the game tree
        if(roll == 0) {
            return any_free(b, player_turn);
        }
        return negamax(b, roll, player_turn, 0U, NEGINF, INF).pos;
    }
}
