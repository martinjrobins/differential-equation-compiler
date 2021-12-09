find_package(Catch2 REQUIRED)

add_library(test_main STATIC test_main.cpp)
target_link_libraries(test_main PUBLIC Catch2::Catch2)
target_link_libraries(test_main PRIVATE project_options)

add_executable(tests test_test.cpp)
target_link_libraries(tests PRIVATE project_options test_main)

include(CTest)
include(Catch)
catch_discover_tests(tests)
