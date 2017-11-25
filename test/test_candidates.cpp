#include <experimental/array>
#include <iostream>
#include "catch.hpp"
#include "solver.h"

namespace Catch {
    template<typename T, std::size_t N>
    struct StringMaker<std::array<T, N> > {
        static std::string convert( std::array<T,N> const& v ) {
            return ::Catch::Detail::rangeToString( v.begin(), v.end() );
        }
    };
}

TEST_CASE("Is a number in a row of the puzzle?", "[num_in_row]" ) {
	{
		solver::Puzzle<2> p = {{{2,0},{1,0}}};
		REQUIRE( solver::IsNumberInRow(p, 2, 0) == true );
		REQUIRE( solver::IsNumberInRow(p, 1, 0) == false );
		REQUIRE( solver::IsNumberInRow(p, 2, 1) == false );
		REQUIRE( solver::IsNumberInRow(p, 1, 1) == true );
	}

	{
		solver::Puzzle<4> p = {{{1,2,3,4},
								{2,3,1,0},
								{0,0,2,1},
								{4,1,0,3}}};

		REQUIRE( solver::IsNumberInRow(p, 2, 0) == true );
		REQUIRE( solver::IsNumberInRow(p, 3, 2) == false );
		REQUIRE( solver::IsNumberInRow(p, 2, 2) == true );
		REQUIRE( solver::IsNumberInRow(p, 2, 3) == false );
		REQUIRE( solver::IsNumberInRow(p, 4, 3) == true );
	}
}
	
TEST_CASE("Is a number in a column of the puzzle?", "[num_in_col]" ) {
	{
		solver::Puzzle<2> p = {{{2,0},{0,1}}};
		REQUIRE( solver::IsNumberInCol(p, 2, 0) == true );
		REQUIRE( solver::IsNumberInCol(p, 1, 0) == false );
		REQUIRE( solver::IsNumberInCol(p, 2, 1) == false );
		REQUIRE( solver::IsNumberInCol(p, 1, 1) == true );
	}
	
	{
		solver::Puzzle<4> p = {{{1,2,3,4},
								{2,3,1,0},
								{0,0,2,1},
								{4,1,0,3}}};

		REQUIRE( solver::IsNumberInCol(p, 2, 0) == true );
		REQUIRE( solver::IsNumberInCol(p, 3, 2) == true );
		REQUIRE( solver::IsNumberInCol(p, 2, 2) == true );
		REQUIRE( solver::IsNumberInCol(p, 4, 2) == false );
		REQUIRE( solver::IsNumberInCol(p, 2, 3) == false );
		REQUIRE( solver::IsNumberInCol(p, 4, 3) == true );
	}
}

TEST_CASE("Is a number in a block of the puzzle?", "[num_in_block]" ) {
	
	{
		solver::Puzzle<4> p = {{{1,2,3,4},
								{4,3,1,0},
								{0,0,2,1},
								{0,1,4,3}}};

		REQUIRE( solver::IsNumberInBlock(p, 1, 0) == true );
		REQUIRE( solver::IsNumberInBlock(p, 2, 0) == true );
		REQUIRE( solver::IsNumberInBlock(p, 3, 0) == true );
		REQUIRE( solver::IsNumberInBlock(p, 4, 0) == true );
		REQUIRE( solver::IsNumberInBlock(p, 1, 1) == true );
		REQUIRE( solver::IsNumberInBlock(p, 2, 1) == false );
		REQUIRE( solver::IsNumberInBlock(p, 3, 1) == true );
		REQUIRE( solver::IsNumberInBlock(p, 4, 1) == true );
		REQUIRE( solver::IsNumberInBlock(p, 1, 2) == true );
		REQUIRE( solver::IsNumberInBlock(p, 2, 2) == false );
		REQUIRE( solver::IsNumberInBlock(p, 3, 2) == false );
		REQUIRE( solver::IsNumberInBlock(p, 4, 2) == false );
		REQUIRE( solver::IsNumberInBlock(p, 1, 3) == true );
		REQUIRE( solver::IsNumberInBlock(p, 2, 3) == true );
		REQUIRE( solver::IsNumberInBlock(p, 3, 3) == true );
		REQUIRE( solver::IsNumberInBlock(p, 4, 3) == true );
	}

}

TEST_CASE("candidates gives incorrect test basics", "[missing_candidate_basics]" ){
	{
		solver::Puzzle<4> p = {{{1,2,3,4},
								{0,3,1,0},
								{0,0,2,1},
								{0,1,0,0}}};
		REQUIRE( solver::IsNumberInBlock(p, 4, 2) == false );
		REQUIRE( solver::IsNumberInRow(p, 4, 3) == false );
		REQUIRE( solver::IsNumberInCol(p, 4, 0) == false );
	}
}

TEST_CASE("list candidates", "[list_candidates]" ) {
	
	{
		solver::Puzzle<4> p = {{{1,2,3,4},
								{4,3,1,0},
								{0,0,2,1},
								{0,1,4,3}}};
		std::array<unsigned, 4> empty{};
		REQUIRE( solver::Candidates(p, 0, 0) == empty );
		REQUIRE( solver::Candidates(p, 0, 1) == empty );
		REQUIRE( solver::Candidates(p, 1, 0) == empty );
		REQUIRE( solver::Candidates(p, 1, 1) == empty );
		REQUIRE( solver::Candidates(p, 0, 2) == empty );
		REQUIRE( solver::Candidates(p, 0, 3) == empty );
		REQUIRE( solver::Candidates(p, 1, 3) == std::experimental::make_array(2u,0,0,0) );
	}
	{
		solver::Puzzle<4> p = {{{1,2,3,4},
								{0,3,1,0},
								{0,0,2,1},
								{0,1,0,0}}};
		REQUIRE( solver::Candidates(p, 3, 0) == std::experimental::make_array(2u,3,4,0) );
	}
}

TEST_CASE("solve with backtrack", "[solve_backtrack]" ) 
{
	{
		solver::Puzzle<4> p = {{{1,2,0,4},
								{4,3,1,0},
								{0,0,2,1},
								{0,1,4,3}}};
		solver::Puzzle<4> solvedP = {{{1,2,3,4},
									  {4,3,1,2},
									  {3,4,2,1},
									  {2,1,4,3}}};
		auto solved = solver::SolveBacktrack(p);
		REQUIRE( solved.has_value() );
		REQUIRE( solved.value() == solvedP );
	}
	{
		solver::Puzzle<9> p = 
						   {{{0,0,3,0,2,0,6,0,0},
							 {9,0,0,3,0,5,0,0,1},
							 {0,0,1,8,0,6,4,0,0},
							 {0,0,8,1,0,2,9,0,0},
							 {7,0,0,0,0,0,0,0,8},
							 {0,0,6,7,0,8,2,0,0},
							 {0,0,2,6,0,9,5,0,0},
							 {8,0,0,2,0,3,0,0,9},
							 {0,0,5,0,1,0,3,0,0}}};
		solver::Puzzle<9> solvedP = 
						      {{{4,8,3,9,2,1,6,5,7},
								{9,6,7,3,4,5,8,2,1},
								{2,5,1,8,7,6,4,9,3}, 
								{5,4,8,1,3,2,9,7,6}, 
								{7,2,9,5,6,4,1,3,8}, 
								{1,3,6,7,9,8,2,4,5}, 
								{3,7,2,6,8,9,5,1,4}, 
								{8,1,4,2,5,3,7,6,9}, 
								{6,9,5,4,1,7,3,8,2}}};
		auto solved = solver::SolveBacktrack(p);
		REQUIRE( solved.has_value() );
		REQUIRE( solved.value() == solvedP );
	}
}
