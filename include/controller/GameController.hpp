#pragma once
#include <memory>
#include "../model/GameModel.hpp"
#include "../view/GameView.hpp"
#include "../utils/state/GameState.hpp"
#include "../utils/state/StartState.hpp"
/**
 * @file GameController.hpp
 * @brief Main controller class for the Monopoly game implementation
 *
 * The GameController class serves as the central coordinator in the MVC (Model-View-Controller)
 * architecture of the Monopoly game. It manages game flow, handles user input, and orchestrates
 * communication between the GameModel and GameView components.
 *
 * Key responsibilities:
 * - Initializes and manages the game model and view components
 * - Processes user input and triggers appropriate model updates
 * - Manages game state transitions
 * - Controls game flow and turn progression
 * - Updates the view based on model changes
 */
namespace monopoly {

/**
 * @class GameController
 * @brief Primary controller class coordinating game logic and user interface
 *
 * The GameController implements the Controller part of the MVC pattern, managing:
 * - Game initialization and setup
 * - State transitions
 * - User input processing
 * - View updates
 * - Game loop control
 */
class GameController {
private:
    /** @brief Friendship declaration for GameState base class */
    friend GameState;
    /** @brief Friendship declaration for StartState class */
    friend StartState;

    /** @brief Pointer to the game's model component */
    std::unique_ptr<GameModel> model;
    /** @brief Pointer to the game's view component */
    std::unique_ptr<GameView> view;
    /** @brief Pointer to the current game state */
    std::unique_ptr<GameState> state;

    /**
     * @brief Initialize the game model with specified number of players
     * @param num_of_players Number of players to participate in the game
     */
    void initModel(size_t num_of_players);

    /**
     * @brief Initialize the game view component
     */
    void initView();

    /**
     * @brief Check if the game has reached its end condition
     * @return true if game is over, false otherwise
     */
    bool isGameOver() const;

    /**
     * @brief Process all user input events
     */
    void handleUserInput();

public:
    /**
     * @brief Constructor for GameController
     *
     * Initializes the controller with default state and empty model/view components
     */
    GameController();

    /**
     * @brief Virtual destructor
     */
    ~GameController() = default;

    /**
     * @brief Start and run the main game loop
     *
     * This method initiates the primary game loop that:
     * - Processes user input
     * - Updates game state
     * - Renders the view
     */
    void run();

    void updatePanelMessage(std::string &message);

    /**
     * @brief Update game state and view
     *
     * Processes one frame of game logic including:
     * - State updates
     * - Model changes
     * - View refreshes
     */
    void update();

    /**
     * @brief Change the current game state
     * @param newState Pointer to the new state to transition to
     */
    void changeState(GameState *newState);

    /**
     * @brief Get the current game model
     * @return Pointer to the current GameModel instance
     */
    GameModel *getModel() const { return model.get(); }

    /**
     * @brief Get the current game view
     * @return Pointer to the current GameView instance
     */
    GameView *getView() const { return view.get(); }
};

} // namespace monopoly