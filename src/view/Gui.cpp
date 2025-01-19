#include "../../include/view/Gui.hpp"

#include <chrono>
#include <stdexcept>

namespace monopoly {
    Gui::Gui() : window(sf::VideoMode(1024, 768), "Monopoly"),
                 diceRolling(false),
                 diceAnimationDuration(sf::seconds(2.0f)),
                 isWindowOpen(true) {
        initWindow();
        initBoard();
        initPlayers();
        initUI();
        initDice();
        initLabels();
    }

    Gui::~Gui() {
        window.close();
    }

    void Gui::initDice() {
        // Initialize dice position and size
        const float diceSize = 40.f;
        const float diceSpacing = 20.f;
        const float startX = board.getPosition().x + (board.getSize().x - (2 * diceSize + diceSpacing)) / 2;
        const float startY = board.getPosition().y + board.getSize().y / 2;

        // Initialize first die
        dice[0].setSize(sf::Vector2f(diceSize, diceSize));
        dice[0].setPosition(startX, startY);
        dice[0].setFillColor(sf::Color::White);
        dice[0].setOutlineThickness(2.f);
        dice[0].setOutlineColor(sf::Color::Black);

        // Initialize second die
        dice[1].setSize(sf::Vector2f(diceSize, diceSize));
        dice[1].setPosition(startX + diceSize + diceSpacing, startY);
        dice[1].setFillColor(sf::Color::White);
        dice[1].setOutlineThickness(2.f);
        dice[1].setOutlineColor(sf::Color::Black);

        // Initialize dice values
        diceValues[0] = 1;
        diceValues[1] = 1;

        diceRolling = false;
        diceAnimationDuration = sf::seconds(1.0f);
    }

    void Gui::renderDiceDots(sf::RenderTarget &target, const sf::RectangleShape &die, int value) {
        const float dieSize = die.getSize().x;
        const float dotRadius = dieSize / 10.f;
        const sf::Vector2f diePos = die.getPosition();

        // Define dot positions relative to die position
        std::vector<sf::Vector2f> dotPositions;

        switch (value) {
            case 1:
                dotPositions.push_back(sf::Vector2f(0.5f, 0.5f));
                break;
            case 2:
                dotPositions.push_back(sf::Vector2f(0.25f, 0.25f));
                dotPositions.push_back(sf::Vector2f(0.75f, 0.75f));
                break;
            case 3:
                dotPositions.push_back(sf::Vector2f(0.25f, 0.25f));
                dotPositions.push_back(sf::Vector2f(0.5f, 0.5f));
                dotPositions.push_back(sf::Vector2f(0.75f, 0.75f));
                break;
            case 4:
                dotPositions.push_back(sf::Vector2f(0.25f, 0.25f));
                dotPositions.push_back(sf::Vector2f(0.75f, 0.25f));
                dotPositions.push_back(sf::Vector2f(0.25f, 0.75f));
                dotPositions.push_back(sf::Vector2f(0.75f, 0.75f));
                break;
            case 5:
                dotPositions.push_back(sf::Vector2f(0.25f, 0.25f));
                dotPositions.push_back(sf::Vector2f(0.75f, 0.25f));
                dotPositions.push_back(sf::Vector2f(0.5f, 0.5f));
                dotPositions.push_back(sf::Vector2f(0.25f, 0.75f));
                dotPositions.push_back(sf::Vector2f(0.75f, 0.75f));
                break;
            case 6:
                dotPositions.push_back(sf::Vector2f(0.25f, 0.25f));
                dotPositions.push_back(sf::Vector2f(0.75f, 0.25f));
                dotPositions.push_back(sf::Vector2f(0.25f, 0.5f));
                dotPositions.push_back(sf::Vector2f(0.75f, 0.5f));
                dotPositions.push_back(sf::Vector2f(0.25f, 0.75f));
                dotPositions.push_back(sf::Vector2f(0.75f, 0.75f));
                break;
        }

        // Draw dots
        sf::CircleShape dot(dotRadius);
        dot.setFillColor(sf::Color::Black);

        for (const auto &pos: dotPositions) {
            dot.setPosition(
                diePos.x + pos.x * dieSize - dotRadius,
                diePos.y + pos.y * dieSize - dotRadius
            );
            target.draw(dot);
        }
    }

    void Gui::rollDice() {
        if (!diceRolling) {
            diceRolling = true;
            diceAnimationClock.restart();

            // Generate random values
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<> dis(1, 6);

            diceValues[0] = dis(gen);
            diceValues[1] = dis(gen);
        }
    }

    void Gui::updateDiceAnimation() {
        if (diceRolling) {
            sf::Time elapsed = diceAnimationClock.getElapsedTime();

            if (elapsed >= diceAnimationDuration) {
                diceRolling = false;
            } else {
                // Generate temporary random values during animation
                static std::random_device rd;
                static std::mt19937 gen(rd());
                static std::uniform_int_distribution<> dis(1, 6);

                // Update temporary dice values for animation
                if (elapsed.asMilliseconds() % 100 < 50) {
                    // Change values every 100ms
                    diceValues[0] = dis(gen);
                    diceValues[1] = dis(gen);
                }

                // Add some rotation or bouncing animation here if desired
                float progress = elapsed.asSeconds() / diceAnimationDuration.asSeconds();
                float scale = 1.0f + sin(progress * 3.14159f) * 0.2f;

                for (auto &die: dice) {
                    sf::Vector2f originalSize = die.getSize();
                    die.setSize(originalSize * scale);
                    die.setPosition(
                        die.getPosition().x - (originalSize.x * (scale - 1.0f) / 2),
                        die.getPosition().y - (originalSize.y * (scale - 1.0f) / 2)
                    );
                }
            }
        }
    }

    void Gui::renderDice() {
        window.draw(dice[0]);
        window.draw(dice[1]);

        // Only render dots if not currently rolling
        if (!diceRolling) {
            renderDiceDots(window, dice[0], diceValues[0]);
            renderDiceDots(window, dice[1], diceValues[1]);
        }
    }

    void Gui::initLabels() {
        const std::vector<std::string> labels = {
            "GO", "Mediterranean\nAvenue", "Community\nChest", "Baltic\nAvenue",
            "Income\nTax", "Reading\nRailroad", "Oriental\nAvenue", "Chance",
            "Vermont\nAvenue", "Connecticut\nAvenue", "Jail/Just\nVisiting",
            "St. Charles\nPlace", "Electric\nCompany", "States\nAvenue",
            "Virginia\nAvenue", "Pennsylvania\nRailroad", "St. James\nPlace",
            "Community\nChest", "Tennessee\nAvenue", "New York\nAvenue",
            "Free\nParking", "Kentucky\nAvenue", "Chance", "Indiana\nAvenue",
            "Illinois\nAvenue", "B. & O.\nRailroad", "Atlantic\nAvenue",
            "Ventnor\nAvenue", "Water\nWorks", "Marvin\nGardens", "Go to\nJail",
            "Pacific\nAvenue", "North Carolina\nAvenue", "Community\nChest",
            "Pennsylvania\nAvenue", "Short Line\nRailroad", "Chance",
            "Park\nPlace", "Luxury\nTax", "Boardwalk"
        };

        squareLabels.resize(40);
        const float squareSize = 70.f;

        for (int i = 0; i < 40; i++) {
            squareLabels[i].setFont(font);
            squareLabels[i].setCharacterSize(8); // Small text size
            squareLabels[i].setFillColor(sf::Color::Black);
            squareLabels[i].setString(labels[i]);

            // Get position of the corresponding square
            sf::Vector2f squarePos = squares[i].getPosition();

            // Center the text in the square
            sf::FloatRect textBounds = squareLabels[i].getLocalBounds();
            squareLabels[i].setOrigin(textBounds.width / 2, textBounds.height / 2);

            // Position text in the center of the square
            squareLabels[i].setPosition(
                squarePos.x + squareSize / 2,
                squarePos.y + squareSize / 2
            );
        }
    }

    void Gui::setWrappedText(Text &text, const std::string &str, float width) {
        std::string wrapped;
        std::string ss(str);
        std::string word;
        float currentWidth = 0;

        while (ss > word) {
            Text tempText = text;
            tempText.setString(word);
            float wordWidth = tempText.getLocalBounds().width;

            if (currentWidth + wordWidth > width) {
                wrapped += "\n" + word + " ";
                currentWidth = wordWidth;
            } else {
                wrapped += word + " ";
                currentWidth += wordWidth;
            }
        }

        text.setString(wrapped);
    }


    // Update the render function to draw labels
    void Gui::render() {
        window.clear(sf::Color(245, 245, 245));

        window.draw(board);
        for (const auto &square: squares) {
            window.draw(square);
        }

        // Draw labels
        for (const auto &label: squareLabels) {
            window.draw(label);
        }

        window.draw(current_player_info);
        window.draw(roll_button);
        window.draw(buy_button);
        window.draw(end_turn_button);
        window.draw(history_panel);
        window.draw(messageText);

        for (const auto &token: playerTokens) {
            window.draw(token);
        }

        window.display();
    }

    void Gui::initBoard() {
        // Main board
        board.setSize(sf::Vector2f(700.f, 700.f));
        board.setPosition(50.f, 25.f);
        board.setFillColor(sf::Color(204, 230, 255)); // Light blue background
        board.setOutlineThickness(2.f);
        board.setOutlineColor(sf::Color::Black);

        const float squareSize = 70.f;
        squares.resize(40);

        // Define all property colors
        const std::vector<sf::Color> propertyColors = {
            sf::Color(110, 60, 30), // Brown (Mediterranean, Baltic)
            sf::Color(135, 206, 235), // Light Blue (Oriental, Vermont, Connecticut)
            sf::Color(255, 0, 255), // Pink/Magenta (St. Charles, States, Virginia)
            sf::Color(255, 140, 0), // Orange (St. James, Tennessee, New York)
            sf::Color(255, 0, 0), // Red (Kentucky, Indiana, Illinois)
            sf::Color(255, 255, 0), // Yellow (Atlantic, Ventnor, Marvin)
            sf::Color(0, 255, 0), // Green (Pacific, North Carolina, Pennsylvania)
            sf::Color(0, 0, 255) // Dark Blue (Park Place, Boardwalk)
        };

        // Initialize all squares as white first
        for (int i = 0; i < 40; i++) {
            squares[i].setSize(sf::Vector2f(squareSize, squareSize));
            squares[i].setFillColor(sf::Color::White);
            squares[i].setOutlineThickness(1.f);
            squares[i].setOutlineColor(sf::Color::Black);
        }

        // Bottom row positions (0-9)
        for (int i = 0; i < 10; i++) {
            squares[i].setPosition(
                board.getPosition().x + (9 - i) * squareSize,
                board.getPosition().y + board.getSize().y - squareSize
            );
        }

        // Left column positions (10-19)
        for (int i = 10; i < 20; i++) {
            squares[i].setPosition(
                board.getPosition().x,
                board.getPosition().y + (19 - i) * squareSize
            );
        }

        // Top row positions (20-29)
        for (int i = 20; i < 30; i++) {
            squares[i].setPosition(
                board.getPosition().x + (i - 20) * squareSize,
                board.getPosition().y
            );
        }

        // Right column positions (30-39)
        for (int i = 30; i < 40; i++) {
            squares[i].setPosition(
                board.getPosition().x + board.getSize().x - squareSize,
                board.getPosition().y + (i - 30) * squareSize
            );
        }

        // Set property colors according to Monopoly board
        // Brown properties
        squares[1].setFillColor(propertyColors[0]); // Mediterranean Avenue
        squares[3].setFillColor(propertyColors[0]); // Baltic Avenue

        // Light Blue properties
        squares[6].setFillColor(propertyColors[1]); // Oriental Avenue
        squares[8].setFillColor(propertyColors[1]); // Vermont Avenue
        squares[9].setFillColor(propertyColors[1]); // Connecticut Avenue

        // Pink/Magenta properties
        squares[11].setFillColor(propertyColors[2]); // St. Charles Place
        squares[13].setFillColor(propertyColors[2]); // States Avenue
        squares[14].setFillColor(propertyColors[2]); // Virginia Avenue

        // Orange properties
        squares[16].setFillColor(propertyColors[3]); // St. James Place
        squares[18].setFillColor(propertyColors[3]); // Tennessee Avenue
        squares[19].setFillColor(propertyColors[3]); // New York Avenue

        // Red properties
        squares[21].setFillColor(propertyColors[4]); // Kentucky Avenue
        squares[23].setFillColor(propertyColors[4]); // Indiana Avenue
        squares[24].setFillColor(propertyColors[4]); // Illinois Avenue

        // Yellow properties
        squares[26].setFillColor(propertyColors[5]); // Atlantic Avenue
        squares[27].setFillColor(propertyColors[5]); // Ventnor Avenue
        squares[29].setFillColor(propertyColors[5]); // Marvin Gardens

        // Green properties
        squares[31].setFillColor(propertyColors[6]); // Pacific Avenue
        squares[32].setFillColor(propertyColors[6]); // North Carolina Avenue
        squares[34].setFillColor(propertyColors[6]); // Pennsylvania Avenue

        // Dark Blue properties
        squares[37].setFillColor(propertyColors[7]); // Park Place
        squares[39].setFillColor(propertyColors[7]); // Boardwalk
    }

    void Gui::initWindow() {
        window.create(sf::VideoMode(1024, 768), "Monopoly Game", sf::Style::Close);
        window.setFramerateLimit(60);

        if (!font.loadFromFile("../../assets/arial.ttf")) {
            throw std::runtime_error("Failed to load font");
        }

        isWindowOpen = true;
    }


    void Gui::initPlayers() {
        const std::vector<sf::Color> playerColors = {
            sf::Color::Red,
            sf::Color::Blue,
            sf::Color::Green,
            sf::Color::Yellow,
            sf::Color::Magenta,
            sf::Color::Cyan,
            sf::Color(255, 165, 0), // Orange
            sf::Color(128, 0, 128) // Purple
        };

        const float tokenRadius = 10.f;
        for (size_t i = 0; i < playerTokens.size(); i++) {
            Circle &token = playerTokens[i];
            token.setRadius(tokenRadius);
            token.setFillColor(playerColors[i]);
            token.setOutlineThickness(1.f);
            token.setOutlineColor(sf::Color::Black);

            token.setPosition(
                board.getPosition().x + board.getSize().x - 40.f,
                board.getPosition().y + board.getSize().y - 40.f
            );
        }
    }

    void Gui::initUI() {
        // Player info panel (Bank card-like appearance)
        current_player_info.setSize(sf::Vector2f(300.f, 150.f));
        current_player_info.setPosition(800.f, 50.f);
        current_player_info.setFillColor(sf::Color(220, 255, 220)); // Light green like a bank note
        current_player_info.setOutlineThickness(2.f);
        current_player_info.setOutlineColor(sf::Color::Black);

        // Roll dice button
        roll_button.setSize(sf::Vector2f(150.f, 40.f));
        roll_button.setPosition(800.f, 220.f);
        roll_button.setFillColor(sf::Color(100, 150, 255)); // Blue button
        roll_button.setOutlineThickness(1.f);
        roll_button.setOutlineColor(sf::Color::Black);

        // Buy button
        buy_button.setSize(sf::Vector2f(150.f, 40.f));
        buy_button.setPosition(800.f, 280.f);
        buy_button.setFillColor(sf::Color(100, 250, 100)); // Green button

        // End turn button
        end_turn_button.setSize(sf::Vector2f(150.f, 40.f));
        end_turn_button.setPosition(800.f, 340.f);
        end_turn_button.setFillColor(sf::Color(250, 100, 100)); // Red button

        // Message text
        messageText.setFont(font);
        messageText.setCharacterSize(16);
        messageText.setFillColor(sf::Color::Black);
        messageText.setPosition(800.f, 400.f);

        // History panel
        history_panel.setSize(sf::Vector2f(300.f, 200.f));
        history_panel.setPosition(800.f, 450.f);
        history_panel.setFillColor(sf::Color::White);
        history_panel.setOutlineThickness(1.f);
        history_panel.setOutlineColor(sf::Color::Black);
    }


    void Gui::processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    isWindowOpen = false;
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                        isWindowOpen = false;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    bool Gui::isOpen() const {
        return isWindowOpen;
    }

    void Gui::close() {
        window.close();
        isWindowOpen = false;
    }

    // Observer pattern implementations
    void Gui::onEvent(const PlayerMoveEvent &event) {
    }

    void Gui::onEvent(const PropertyPurchaseEvent &event) {
    }

    void Gui::onEvent(const BankruptcyEvent &event) {
    }

    void Gui::onEvent(const DiceRollEvent &event) {
    }

    void Gui::onEvent(const MoneyChangeEvent &event) {
    }

    void Gui::onEvent(const GameOverEvent &event) {
    }

    // UI interaction methods
    void Gui::showDialog(const std::string &message) {
        messageText.setString(message);
    }

    bool Gui::getYesNoResponse(const std::string &question) {
        // TODO: Implement proper dialog
        return false;
    }

    void Gui::displayError(const std::string &error) {
        messageText.setString("Error: " + error);
    }
} // namespace monopoly