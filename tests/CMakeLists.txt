
enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(monopoly_tests
        main_test.cpp
        model/squares/PropertyTest.cpp
        model/squares/SquareTest.cpp
        model/squares/StreetTest.cpp
        model/squares/RailroadTest.cpp
        model/squares/UtilityTest.cpp
)

target_link_libraries(monopoly_tests
        PRIVATE
        GTest::GTest
        GTest::Main
)

target_include_directories(monopoly_tests
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

gtest_discover_tests(monopoly_tests)