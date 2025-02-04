#pragma once
#include <memory>
#include "../model/GameModel.hpp"
#include "../view/GameView.hpp"
#include "../utils/state/GameState.hpp"
#include "../utils/state/StartState.hpp"

namespace monopoly {
    class GameState;
    class StartState;

    class GameController {
    private:
        friend GameState;
        friend StartState;

        std::unique_ptr<GameModel> model;
        std::unique_ptr<GameView> view;
        std::unique_ptr<GameState> state;


        void initModel(size_t num_of_players);

        void initView();

        bool isGameOver() const;

        void handleKeyRelease(sf::Keyboard::Key key);

        void handleUserInput();

    public:
        GameController();

        ~GameController() = default;

        void run();

        void update();


        void changeState(GameState *newState);

        // Accessors for states
        GameModel *getModel() const { return model.get(); }
        GameView *getView() const { return view.get(); }
        size_t getCurrentPlayerIndex() const { return current_player_index; }
        void setCurrentPlayerIndex(const size_t index) { current_player_index = index; }
    };
}
