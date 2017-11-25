include_directories(thirdparty)
set(TEST_INCLUDE catch.hpp)

add_executable(test_candidates ${SOLVER_HEADERS} ${TEST_INCLUDE} test_candidates.cpp
		test_main.cpp)
add_test(test_candidates test_candidates)
