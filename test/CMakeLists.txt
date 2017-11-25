include_directories(${THIRDPARTY_DIR})
set(TEST_INCLUDE ${THIRDPARTY_DIR}/catch.hpp)

add_executable(test_candidates ${SOLVER_HEADERS} ${TEST_INCLUDE} test_candidates.cpp
		test_main.cpp)
add_test(test_candidates test_candidates)
