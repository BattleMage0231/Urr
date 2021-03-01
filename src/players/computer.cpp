#include <ur/players/computer.h>

namespace ur {
    namespace players {
        AIPlayer::AIPlayer(Color turn) {
            player_turn = turn;
        }

        int AIPlayer::find_any(bool* pieces, int rem) {
            if(rem > 0) {
                return OFF_BOARD;
            }
            for(int i = 0; i < BOARD_SIZE; ++i) {
                if(pieces[i]) {
                    return i;
                }
            }
            throw;
        }

        double AIPlayer::get_avg(Board& b, int depth, Color turn, double alpha, double beta) {
            double rates[] = {0.0625, 0.25, 0.375, 0.25, 0.0625};
            double ans = 0;
            for(int i = 0; i <= NUM_DICE; ++i) {
                ans += rates[i] * negamax(b, i, turn, depth, alpha, beta).second;
            }
            return ans;
        }

        std::pair<double, int> AIPlayer::negamax(Board& b, int roll, Color turn, int depth, double alpha, double beta) {
            if(b.winner() || depth > 4) {
                return std::make_pair(NULL_POS, value_of(b, turn));
            }
            if(roll == 0) {
                int any_free = find_any(b.get_pieces(turn), b.get_rem(turn));
                b.move_piece(any_free, any_free + roll, turn);
                double avg = -get_avg(b, depth + 1, opposite(turn), -beta, -alpha);
                b.undo_last();
                return std::make_pair(any_free, avg);
            }
            if(!b.has_valid(roll, turn)) {
                b.no_moves(turn);
                double avg = -get_avg(b, depth + 1, opposite(turn), -beta, -alpha);
                b.undo_last();
                return std::make_pair(NULL_POS, avg);
            }
            std::vector<std::pair<double, int>> moves;
            for(int i = OFF_BOARD; i < BOARD_SIZE; ++i) {
                if(b.is_valid(roll, i, turn)) {
                    b.move_piece(i, i + roll, turn);
                    if(!is_rosette(i + roll)) {
                        moves.push_back(std::make_pair(-value_of(b, opposite(turn)), i));
                    } else {
                        moves.push_back(std::make_pair(value_of(b, turn), i));
                    }
                    b.undo_last();
                }
            }
            std::sort(moves.begin(), moves.end());
            double cmax = NEGINF;
            int mmax = NULL_POS;
            for(int i = (int) moves.size() - 1; i >= 0; --i) {
                int tile = moves[i].second;
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
            return std::make_pair(mmax, cmax);
        }

        double AIPlayer::value_of(Board& b, Color turn) {
            bool* pieces = b.get_pieces(turn);
            int rem = b.get_rem(turn);
            bool* opp_pieces = b.get_pieces(opposite(turn));
            int opp_rem = b.get_rem(opposite(turn));
            int board = 0;
            int opp_board = 0;
            double val = 0;
            double loc_vals[BOARD_SIZE] = {
                1.02, 1.30, 1.27, 1.93, 1.28, 1.33, 1.38, 2.38, 1.46, 1.44, 1.38, 1.35, 2.20, 1.75
            };
            for(int i = 0; i < BOARD_SIZE; ++i) {
                if(pieces[i]) {
                    ++board;
                    val += loc_vals[i];
                }
                if(opp_pieces[i]) {
                    ++opp_board;
                    val -= loc_vals[i];
                }
            }
            int done = NUM_PIECES - board - rem;
            int opp_done = NUM_PIECES - opp_board - opp_rem;
            return val + 10.0 * done + 2.0 * board - 10.0 * opp_done - 2.0 * opp_board;
        }

        int AIPlayer::get_move(Board b, int roll) {
            if(roll == 0) {
                return find_any(b.get_pieces(player_turn), b.get_rem(player_turn));
            }
            return negamax(b, roll, player_turn, 0, NEGINF, INF).first;
        }
    }
}
