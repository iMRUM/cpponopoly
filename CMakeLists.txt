# CMakeLists.txt

cmake_minimum_required(VERSION 3.29)
project(Monopoly)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(model_tests
        src/model/Game.cpp
        include/model/Game.hpp
        src/model/Board.cpp
        include/model/Board.hpp
        src/model/Player.cpp
        include/utils/Strategy/StrategyRentCalculator.hpp
        include/utils/Id.hpp
        include/utils/registries/Registry.hpp
        include/utils/registries/PropertyRegistry.hpp
        src/utils/Registry/PropertyRegistry.cpp
        include/utils/registries/PlayerRegistry.hpp
        include/utils/Strategy/strategy/RentCalculator.hpp
        include/utils/Strategy/StreetRentCalculator.hpp
        include/utils/Strategy/RailroadRentCalculator.hpp
        include/utils/Strategy/UtilityRentCalculator.hpp
        include/controller/Controller.hpp
        include/view/Gui.hpp
        include/view/SFMLGui.hpp
        src/controller/Controller.cpp
        include/utils/Observer/IObserver.hpp
        include/utils/Observer/IObservable.hpp
        include/utils/Observer/IMultiObservable.hpp
        include/view/MonopolyObserver.hpp
        src/view/Gui.cpp
        maeein.cpp
        src/view/main.cpp
        tests/utils/Id_tests.cpp
        tests/model/squares/tests.cpp
        tests/utils/Registry_test.cpp
        tests/model/Game_test.cpp
        tests/view/Gui_test.cpp
)
