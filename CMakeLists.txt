# CMakeLists.txt

cmake_minimum_required(VERSION 3.29)
project(Monopoly)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(model_tests
        src/model/Game.cpp
        include/model/Game.hpp
        src/model/Player.cpp
        include/utils/Strategy/StrategyRentCalculator.hpp
        include/utils/Strategy/StreetRentCalculator.hpp
        include/utils/Strategy/RailroadRentCalculator.hpp
        include/utils/Strategy/UtilityRentCalculator.hpp
        include/controller/Controller.hpp
        include/view/Gui.hpp
        src/controller/Controller.cpp
        include/utils/Observer/IMonopolyObserver.hpp
        src/view/Gui.cpp
        maeein.cpp
        src/view/main.cpp
        tests/model/squares/tests.cpp
        tests/model/Game_test.cpp
        include/utils/registry/IRegistry.hpp
        include/utils/registry/SquareRegistry.hpp
        include/utils/factory/IFactory.hpp
        include/utils/factory/SquareFactory.hpp
        include/utils/factory/test.cpp
        include/view/components/SFComponent.hpp
        include/view/components/Button.hpp
        src/view/main_button_.cpp
        include/view/components/Button.hpp
        src/view/components/Button.cpp
        include/view/components/BoardSquare.hpp
        src/view/components/BoardSquare.cpp
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
        src/utils/registry/PlayerRegistry.cpp
        include/utils/registry/PlayerRegistry.hpp
        tests/utils/player_registry_test.cpp
        src/utils/registry/SquareRegistry.cpp
        tests/utils/square_registry_test.cpp
        include/view/components/SFComposite.hpp
        include/view/components/BoardView.hpp
        src/view/components/BoardView.cpp
        include/view/components/UserView.hpp
        include/view/components/Window.hpp
        include/view/View.hpp
        src/view/View.cpp
        src/view/components/UserView.cpp
        src/view/main_button.cpp
        include/model/Rules.hpp
)
