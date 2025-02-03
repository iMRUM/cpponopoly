# CMakeLists.txt

cmake_minimum_required(VERSION 3.29)
project(Monopoly)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(model_tests
        src/model/GameModel.cpp
        include/model/GameModel.hpp
        src/model/Player.cpp
        include/utils/strategy/StrategyRentCalculator.hpp
        include/utils/strategy/StreetRentCalculator.hpp
        include/utils/strategy/RailroadRentCalculator.hpp
        include/utils/strategy/UtilityRentCalculator.hpp
        include/controller/GameController.hpp
        include/view/Gui.hpp
        src/controller/GameController.cpp
        main.cpp
        tests/model/squares/tests.cpp
        tests/model/Game_test.cpp
        include/view/components/SFComponent.hpp
        include/view/components/Button.hpp
        include/view/components/Button.hpp
        src/view/components/Button.cpp
        include/view/components/BoardSquareComponent.hpp
        src/view/components/BoardSquareComponent.cpp
        include/view/components/StreetSquare.hpp
        src/view/components/StreetSquare.cpp
        include/view/components/CornerSquare.hpp
        include/view/components/CommunityChestSquare.hpp
        include/view/components/IncomeTaxSquare.hpp
        include/view/components/RailroadSquare.hpp
        src/view/components/CommunityChestSquare.cpp
        src/view/components/IncomeTaxSquare.cpp
        include/view/components/ChanceSquare.hpp
        src/view/components/ChanceSquare.cpp
        src/view/components/RailroadSquare.cpp
        include/view/components/JailSquare.hpp
        src/view/components/JailSquare.cpp
        include/view/components/FreeParkingSquare.hpp
        src/view/components/FreeParkingSquare.cpp
        include/view/components/GoToJailSquare.hpp
        src/view/components/GoToJailSquare.cpp
        include/view/components/GoSquare.hpp
        src/view/components/GoSquare.cpp
        include/view/components/UtilitySquare.hpp
        src/view/components/UtilitySquare.cpp
        include/view/components/MonopolyBoard.hpp
        src/view/components/MonopolyBoard.cpp
        include/view/components/SFComposite.hpp
        include/view/components/BoardView.hpp
        src/view/components/BoardView.cpp
        include/view/components/UserView.hpp
        include/view/components/Window.hpp
        include/view/GameView.hpp
        src/view/GameView.cpp
        src/view/components/UserView.cpp
        include/model/MonopolyRules.hpp
        include/model/Board.hpp
        src/model/Board.cpp
        include/controller/TurnController.hpp
        include/controller/PropertyController.hpp
        src/controller/TurnController.cpp
        src/controller/PropertyController.cpp
        include/view/components/BoardSquareComposite.hpp
        include/view/components/PlayerTokenComponent.hpp
        src/view/components/PlayerTokenComponent.cpp
        include/utils/state/IMonopolyState.hpp
        src/view/components/PlayerTokenComponent.cpp
)
