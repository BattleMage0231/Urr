#pragma once

#include <iostream>
#include <limits>
#include <random>

namespace ur {
    /** The size of the Ur board. */
    constexpr int BOARD_SIZE = 14;

    /** The number of total pieces. */
    constexpr int NUM_PIECES = 7;

    /** The number of binary dices. */
    constexpr int NUM_DICE = 4;

    /** A constant for a null tile position. */
    constexpr int NULL_POS = -2;

    /** A constant for an off tile position. */
    constexpr int OFF_BOARD = -1;

    /** The maximum double value supported by the system. */
    const double INF = std::numeric_limits<double>::max();

    /** The minimum double value supported by the system. */
    const double NEGINF = std::numeric_limits<double>::lowest();

    /** A color of a player in an Ur game. */
    enum class Color { WHITE, BLACK };

    /**
     * Overloads the << operator to support the Color enum.
     * Allows direct output of Color to std::cout.
     * 
     * @param str the output stream
     * @param c the Color
     * @return the output stream reference. 
     */
    std::ostream& operator<<(std::ostream& str, const Color& c);

    /**
     * Returns the opposite of a color.
     *
     * @param orig the color
     * @return the other color
     */
    Color opposite(Color orig) noexcept;

    /** A random number generator. */
    extern std::mt19937 rng;

    /**
     * Sets the seed for the random number generator.
     *
     * @param seed the seed
     */
    void set_seed(unsigned seed);

    /** A move in an Ur game. */
    struct Move {
        /** Whether the current player had a valid move. */
        bool has_move;

        /** The current player's color. */
        Color turn;

        /** The original position of the moved piece. */
        int orig;

        /** The new piece position. */
        int loc;

        /** Whether the move took an opponent piece. */
        bool took_piece;
    };

    /**
     * Gets whether a tile is in the competition zone.
     *
     * @param tile the tile
     * @return whether it is in the competition zone
     */
    bool is_competition(int tile) noexcept;

    /**
     * Gets whether a tile is a rosette tile.
     *
     * @param tile the tile
     * @return whether it is a rosette tile
     */
    bool is_rosette(int tile) noexcept;

    /**
     * Gets whether a tile position is on the board.
     *
     * @param tile the tile position
     * @return whether it is on the board
     */
    bool is_board(int tile) noexcept;

    /**
     * Gets whether a tile exists (is on the board or not yet started).
     * Returns false for finished pieces.
     *
     * @param tile the tile
     * @return whether the tile exists
     */
    bool tile_exists(int tile) noexcept;
}
