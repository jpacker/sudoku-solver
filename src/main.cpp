#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

#include "solver.h"

template <std::size_t N>
solver::Puzzle<N> LoadPuzzle(const std::string& fileName)
{
	solver::Puzzle<N> p{};
	std::ifstream f{fileName};
	std::array<char, N+1> a;
	for(std::size_t i = 0; i < N; ++i)
	{
		f.getline(&a[0], N+1);
		auto& puzzleRow = p[i];
		std::transform(std::begin(a), std::end(a), std::begin(puzzleRow),
				[](const auto c)
				{
					return static_cast<unsigned>(c - '0');
				}
				);
	}
	return p;
}

template <std::size_t N>
void LoadSolvePrint(const std::string& fileName)
{
	using solver::operator<<;
	const auto p = LoadPuzzle<N>(fileName);
	const auto solved = solver::SolveBacktrack(p);
	if(solved.has_value())
	{
		std::cout << solved.value();
	}
	else
	{
		std::cout << "could not solve the puzzle" << '\n';
	}
}

int main() 
{
	size_t n = 0;
	std::string fileName;
	std::cin >> n;
	std::cin >> fileName;
	switch(n)
	{
		case 4:
			LoadSolvePrint<4>(fileName);
			break;
		case 9:
			LoadSolvePrint<9>(fileName);
			break;
		case 16:
			LoadSolvePrint<16>(fileName);
			break;
		default:
			std::cout << "Only accepts boards of 4x4, 9x9, and 16x16" << '\n';
			break;
	}
}

