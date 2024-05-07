

find_package(Boost COMPONENTS system unit_test_framework REQUIRED)

# Include Boost headers
include_directories(${Boost_INCLUDE_DIRS})

add_executable( UnitTests test_myMathVector.cpp )

# Link myMath Library and Boost Unit Test Framework
target_link_libraries( UnitTests mathlib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )

enable_testing()
add_test(NAME UnitTests COMMAND UnitTests)