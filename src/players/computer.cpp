#include <ur/players/computer.h>

namespace ur {
    namespace players {
        ai_player::ai_player(bool white) {
            is_white = white;
        }

        double ai_player::value_of(board& b, bool white_turn) {
            bool* pieces = b.get_pieces(white_turn);
            int rem = b.get_rem(white_turn);
            bool* opp_pieces = b.get_pieces(!white_turn);
            int opp_rem = b.get_rem(!white_turn);
            int board = 0;
            int opp_board = 0;
            double val = 0;
            double loc_vals[] = {
                1.02, 1.30, 1.27, 1.93, 1.28, 1.33, 1.38, 2.38, 1.46, 1.44, 1.38, 1.35, 2.20, 1.75
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
            int done = 7 - board - rem;
            int opp_done = 7 - opp_board - opp_rem;
            return val + 10.0 * done + 2.0 * board - 10.0 * opp_done - 2.0 * opp_board;
        }

        double ai_player::get_avg(board& b, int depth, bool white_turn, double alpha, double beta) {
            double rates[] = {0.0625, 0.25, 0.375, 0.25, 0.0625};
            double ans = 0;
            for(int i = 0; i <= 4; ++i) {
                ans += rates[i] * negamax(b, i, white_turn, depth, alpha, beta).second;
            }
            return ans;
        }

        int ai_player::find_any(bool* pieces, int rem) {
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

        std::pair<int, double> ai_player::negamax(board& b, int roll, bool white_turn, int depth, double alpha, double beta) {
            if(b.winner() || depth > 4) {
                return std::make_pair(-2, value_of(b, white_turn));
            }
            if(roll == 0) {
                int any_free = find_any(b.get_pieces(white_turn), b.get_rem(white_turn));
                b.move_piece(any_free, any_free + roll, white_turn);
                std::pair<int, double> ans = std::make_pair(any_free, -get_avg(b, depth + 1, !white_turn, -beta, -alpha));
                b.undo_last();
                return ans;
            }
            if(!b.has_valid(roll, white_turn)) {
                b.no_moves(white_turn);
                std::pair<int, double> ans = std::make_pair(-2, -get_avg(b, depth + 1, !white_turn, -beta, -alpha));
                b.undo_last();
                return ans;
            }
            std::vector<std::pair<double, int>> moves;
            for(int i = -1; i < 14; ++i) {
                if(b.is_valid(roll, i, white_turn)) {
                    b.move_piece(i, i + roll, white_turn);
                    if(!b.is_rosette(i + roll)) {
                        moves.push_back(std::make_pair(-value_of(b, !white_turn), i));
                    } else {
                        moves.push_back(std::make_pair(value_of(b, white_turn), i));
                    }
                    b.undo_last();
                }
            }
            std::sort(moves.begin(), moves.end());
            double cmax = -std::numeric_limits<double>::max();
            int mmax = -2;
            for(int i = (int) moves.size() - 1; i >= 0; --i) {
                int tile = moves[i].second;
                if(!b.is_valid(roll, tile, white_turn)) {
                    throw tile;
                }
                b.move_piece(tile, tile + roll, white_turn);
                double ans;
                if(!b.is_rosette(tile + roll)) {
                    ans = -get_avg(b, depth + 1, !white_turn, -beta, -alpha);
                } else {
                    ans = get_avg(b, depth + 1, white_turn, alpha, beta);
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

        int ai_player::get_move(bool* pieces, int rem, bool* opp_pieces, int opp_rem, int roll) {
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
            board b;
            if(is_white) {
                b = board(pieces, rem, opp_pieces, opp_rem);
            } else {
                b = board(opp_pieces, opp_rem, pieces, rem);
            }
            double inf = std::numeric_limits<double>::max();
            double neginf = -inf;
            std::pair<int, double> ans = negamax(b, roll, is_white, 0, neginf, inf);
            return ans.first;
        }
    }
}
