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
        src/model/player/Player.cpp
        src/model/squares/Square.cpp
        src/model/squares/Square.hpp
        src/model/squares/Property.cpp
        src/model/squares/Property.hpp
        include/utils/Strategy/StrategyRentCalculator.hpp
        include/utils/Id.hpp
        include/utils/registries/Registry.hpp
        include/utils/registries/PropertyRegistry.hpp
        src/registries/PropertyRegistry.cpp
        include/utils/registries/PlayerRegistry.hpp
        src/model/squares/Railroad.hpp
        src/model/squares/Utility.hpp
        src/model/squares/Street.hpp
        src/controller/GameController.hpp
        src/controller/GameController.hpp
        src/controller/GameController.cpp
        include/utils/Strategy/strategy/RentCalculator.hpp
        include/utils/Strategy/StreetRentCalculator.hpp
        include/utils/Strategy/RailroadRentCalculator.hpp
        include/utils/Strategy/UtilityRentCalculator.hpp
        src/model/squares/SpecialSquare.cpp
        include/controller/Controller.hpp
        include/view/Gui.hpp
        include/view/SFMLGui.hpp
        src/controller/Controller.cpp
        include/patterns/Observer/IObserver.hpp
        include/patterns/Observer/IObservable.hpp
        include/patterns/Observer/IMultiObservable.hpp
        include/view/MonopolyObserver.hpp
        src/view/Gui.cpp
        maeein.cpp
        src/view/main.cpp
)
