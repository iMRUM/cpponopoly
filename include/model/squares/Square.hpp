#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace monopoly {
    /**
     * @brief Base class for all squares on the Monopoly board
     *
     * Square represents a position on the Monopoly board that a player can land on.
     * It serves as the base class for all specific square types (properties, special squares, etc.).
     * Each square has a unique name, position on the board, and ID.
     */
    class Square {
    private:
        std::string name;    ///< The display name of the square
        int position;        ///< The position of the square on the board (0-based)
        int id;             ///< Unique identifier for the square (currently same as position)

    public:
        /**
         * @brief Constructs a new Square
         * @param name The display name of the square
         * @param position The position on the board (0-based)
         * @throw std::invalid_argument if name is empty or position is negative
         */
        Square(const std::string &name, const int position)
            : name(name), position(position), id(position) {
            if (name.empty()) {
                throw std::invalid_argument("Square name cannot be empty");
            }
            if (position < 0) {
                throw std::invalid_argument("Invalid board position: negative position");
            }
        }

        /**
         * @brief Virtual destructor to ensure proper cleanup of derived classes
         */
        virtual ~Square() noexcept = default;

        /**
         * @brief Gets the display name of the square
         * @return The square's name
         */
        [[nodiscard]] const std::string &getName() const noexcept { return name; }

        /**
         * @brief Gets the position of the square on the board
         * @return The square's position (0-based)
         */
        [[nodiscard]] int getPosition() const noexcept { return position; }

        /**
         * @brief Gets the unique identifier of the square
         * @return The square's ID
         */
        [[nodiscard]] int getId() const noexcept { return id; }

        // Disable copying and moving to prevent duplicate squares
        Square(const Square &) = delete;
        Square &operator=(const Square &) = delete;
        Square(Square &&) = delete;
        Square &operator=(Square &&) = delete;
    };
}