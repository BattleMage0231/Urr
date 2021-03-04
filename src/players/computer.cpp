#include <ur/players/computer.h>

namespace ur {
    namespace players {
        bool AIPlayer::Node::operator <(const AIPlayer::Node& other) const {
            return value < other.value;
        }

        AIPlayer::AIPlayer(Color turn, unsigned max_depth) 
            : player_turn(turn) 
            , max_depth(max_depth)
        {}

        int AIPlayer::any_free(Board& b, Color turn) {
            if(b.get_rem(turn) > 0) {
                return OFF_BOARD;
            }
            for(int i = 0; i < BOARD_SIZE; ++i) {
                if(b.has_piece(i, turn)) {
                    return i;
                }
            }
            throw;
        }

        double AIPlayer::get_avg(Board& b, unsigned depth, Color turn, double alpha, double beta) {
            double rates[] = {0.0625, 0.25, 0.375, 0.25, 0.0625};
            double ans = 0;
            for(int i = 0; i <= NUM_DICE; ++i) {
                ans += rates[i] * negamax(b, i, turn, depth, alpha, beta).value;
            }
            return ans;
        }

        AIPlayer::Node AIPlayer::negamax(Board& b, int roll, Color turn, unsigned depth, double alpha, double beta) {
            if(b.finished() || depth > max_depth) {
                return Node {
                    .pos = NULL_POS,
                    .value = value_of(b, turn)
                };
            }
            if(roll == 0) {
                int free_piece = any_free(b, turn);
                b.move_piece(free_piece, free_piece + roll, turn);
                double avg = -get_avg(b, depth + 1, opposite(turn), -beta, -alpha);
                b.undo_last();
                return Node {
                    .pos = free_piece,
                    .value = avg
                };
            }
            if(!b.has_valid(roll, turn)) {
                b.no_moves(turn);
                double avg = -get_avg(b, depth + 1, opposite(turn), -beta, -alpha);
                b.undo_last();
                return Node {
                    .pos = NULL_POS,
                    .value = avg
                };
            }
            std::vector<Node> moves;
            for(int i = OFF_BOARD; i < BOARD_SIZE; ++i) {
                if(b.is_valid(roll, i, turn)) {
                    b.move_piece(i, i + roll, turn);
                    Node cur { .pos = i };
                    if(!is_rosette(i + roll)) {
                        cur.value = -value_of(b, opposite(turn));
                    } else {
                        cur.value = value_of(b, turn);
                    }
                    moves.push_back(cur);
                    b.undo_last();
                }
            }
            std::sort(moves.begin(), moves.end());
            double cmax = NEGINF;
            int mmax = NULL_POS;
            for(auto it = moves.rbegin(); it != moves.rend(); ++it) {
                int tile = (*it).pos;
                b.move_piece(tile, tile + roll, turn);
                double ans;
                if(!is_rosette(tile + roll)) {
                    ans = -get_avg(b, depth + 1, opposite(turn), -beta, -alpha);
                } else {
                    ans = get_avg(b, depth + 1, turn, alpha, beta);
                }
                b.undo_last();
                if(ans >= cmax) {
                    cmax = ans;
                    mmax = tile;
                }
                alpha = std::max(alpha, cmax);
                if(beta <= alpha) {
                    break;
                }
            }
            return Node {
                .pos = mmax,
                .value = cmax
            };
        }

        double AIPlayer::value_of(Board& b, Color turn) {
            double val = 0;
            double loc_vals[BOARD_SIZE] = {
                1.02, 1.30, 1.27, 1.93, 1.28, 1.33, 1.38, 2.38, 1.46, 1.44, 1.38, 1.35, 2.20, 1.75
            };
            for(int i = 0; i < BOARD_SIZE; ++i) {
                if(b.has_piece(i, turn)) {
                    val += loc_vals[i];
                }
                if(b.has_piece(i, opposite(turn))) {
                    val -= loc_vals[i];
                }
            }
            int rem = b.get_rem(turn);
            int opp_rem = b.get_rem(opposite(turn));
            int done = b.get_done(turn);
            int opp_done = b.get_done(opposite(turn));
            int board = NUM_PIECES - rem - done;
            int opp_board = NUM_PIECES - opp_rem - opp_done;
            return val + 10.0 * done + 2.0 * board - 10.0 * opp_done - 2.0 * opp_board;
        }

        int AIPlayer::get_move(Board b, int roll) {
            if(roll == 0) {
                return any_free(b, player_turn);
            }
            return negamax(b, roll, player_turn, 0U, NEGINF, INF).pos;
        }
    }
}
