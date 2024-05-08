
enable_testing()

find_package(Boost COMPONENTS system unit_test_framework REQUIRED)

# Include Boost headers
include_directories(${Boost_INCLUDE_DIRS})

set(TestList Vector
             MatrixNonSquare
             )

foreach(test ${TestList})

    add_executable( ${test}UnitTest test_myMath${test}.cpp )

    target_link_libraries( ${test}UnitTest mathlib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )

    add_test(NAME ${test}UnitTest
             COMMAND ${test}UnitTest)
             
endforeach(test)