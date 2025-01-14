# CMakeLists.txt

cmake_minimum_required(VERSION 3.29)
project(Monopoly)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(model_tests
        src/model/Game.cpp
        src/model/Game.hpp
        src/model/Board.cpp
        src/model/Board.hpp
        src/model/player/Player.cpp
        src/model/squares/Square.cpp
        src/model/squares/Square.hpp
        src/model/squares/Property.cpp
        src/model/squares/Property.hpp
        include/StrategyRentCalculator.hpp
        include/utils/Id.hpp
        include/registries/Registry.hpp
        include/registries/PropertyRegistry.hpp
        src/registries/PropertyRegistry.cpp
        include/registries/PlayerRegistry.hpp
        src/model/squares/Railroad.hpp
        src/model/squares/Utility.hpp
        src/model/squares/Street.hpp
        src/controller/GameController.hpp
        src/controller/GameController.hpp
        src/controller/GameController.cpp
)
